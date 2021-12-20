abstract type AbstractPacket end

struct LiteralValuePacket <: AbstractPacket
    version::UInt8
    value::Int
    payload::String # rest of the original payload after pasrsing this packet
    function LiteralValuePacket(bits::String)
        ver = parse(Int, bits[1:3], base = 2)

        ind = 7
        to_decode = ""
        while true
            tmp = bits[ind+1:ind+4]
            to_decode = to_decode * tmp
            bits[ind] == '1' || break
            ind += 5
        end
        value = parse(Int, to_decode, base = 2)
        payload = bits[ind+5:end]
        new(ver, value, payload)
    end
end

function initialize_packet(bits)
    if get_packet_type(bits) == 4
        return LiteralValuePacket(bits)
    else
        return OperatorPacket(bits)
    end
end

mutable struct OperatorPacket <: AbstractPacket
    version::UInt8
    type::UInt8
    payload::String
    subpackets::Vector{AbstractPacket}
    value::Int

    function OperatorPacket(bits::String)
        ver = parse(Int, bits[1:3], base = 2)
        type = parse(Int, bits[4:6], base = 2)
        length_type_id = parse(Bool, bits[7])

        offset = length_type_id ? 11 : 15
        length = parse(Int, bits[8:8+offset-1], base = 2)
        payload = bits[8+offset:end]

        subpackets = []
        if length_type_id == true # We got number of packets
            for subp = 1:length
                p = initialize_packet(payload)
                push!(subpackets, p)
                payload = p.payload
            end
        else # We got length of subpackets
            offset = 8 + offset
            local_payload = bits[offset:offset+length-1]

            while count(x -> x == '1', local_payload) != 0
                p = initialize_packet(local_payload)
                push!(subpackets, p)
                local_payload = p.payload
            end
            payload = bits[offset+length:end]
        end
        new(ver, type, payload, subpackets, -1)
    end
end


function get_packet_type(bits)
    return parse(Int, bits[4:6], base = 2)
end


function get_version_sum(packet::AbstractPacket, version_sum)
    version_sum += packet.version
    if typeof(packet) == LiteralValuePacket
        return version_sum
    end

    for p in packet.subpackets
        if typeof(p) == LiteralValuePacket
            version_sum += p.version
        else
            version_sum = get_version_sum(p, version_sum)
        end
    end
    return version_sum
end


dispatcher = Dict(
    [(0, sum),
    (1, prod),
    (2, minimum),
    (3, maximum),
    (5, (x) -> x[1] > x[2]),
    (6, (x) -> x[1] < x[2]),
    (7, (x) -> x[1] == x[2])]
)

function evaluate_packets(packet::AbstractPacket)
    if typeof(packet) == LiteralValuePacket
        return packet.value
    else
        subpacket_values = []
        for p in packet.subpackets
            if p.value != -1
                push!(subpacket_values, p.value)
            else
                push!(subpacket_values, evaluate_packets(p))
            end

        end
        packet.value = dispatcher[packet.type](subpacket_values)
        return packet.value
    end
end


function main()
    f = open("inputs/16.txt", "r")
    packets = read(f, String)
    bytes = hex2bytes(packets)

    bits = join([bitstring(byte) for byte in bytes])

    p = initialize_packet(bits)

    println("First part: ", get_version_sum(p, 0))
    println("Second part: ", evaluate_packets(p))
end

main()