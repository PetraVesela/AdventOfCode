#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <limits>
#include <algorithm>

using int64 = long long;

constexpr int64 TILE_WIDTH = 1;

struct Position
{
    Position(int64 inX, int64 inY) :
        x(inX),
        y(inY)
    {}

    Position() = default;

    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }

    int64 x = -1;
    int64 y = -1;
};

struct PositionHash
{
    size_t operator()(const Position& p) const noexcept
    {
        return std::hash<int64>{}(p.x) ^ (std::hash<int64>{}(p.y) << 1);
    }
};

using PositionSet = std::unordered_set<Position, PositionHash>;


PositionSet getPerimeterPositions(const std::vector<Position>& cornerTilePositions)
{
    PositionSet perimeterPositions;

    if (cornerTilePositions.size() == 2)
    {
        perimeterPositions.insert(cornerTilePositions[0]);
        perimeterPositions.insert(cornerTilePositions[1]);
        return perimeterPositions;
    }

    for (int iCorner = 0; iCorner < cornerTilePositions.size(); ++iCorner)
    {
        const Position cornerPos = cornerTilePositions[iCorner];
        const Position nextCornerPos = (iCorner == cornerTilePositions.size() - 1) ?
            cornerTilePositions[0] :
            cornerTilePositions[iCorner + 1];

        assert(cornerPos.x == nextCornerPos.x || cornerPos.y == nextCornerPos.y);

        const bool isVertical = cornerPos.x == nextCornerPos.x;
        int64 start = -1;
        int64 end = -1;
        if (isVertical)
        {
            start = cornerPos.y;
            end = nextCornerPos.y;
        }
        else
        {
            start = cornerPos.x;
            end = nextCornerPos.x;
        }
        const int sign = start < end ? 1 : -1;

        for (int64 j = start; j != end; j += sign)
        {
            if (isVertical)
            {
                perimeterPositions.insert({ cornerPos.x, j });
            }
            else
            {
                perimeterPositions.insert({ j, cornerPos.y });
            }
        }
    }

    return perimeterPositions;
}


PositionSet allColoredTiles;
PositionSet allEmptyTiles;
// if you ever hit a bound that's not a perimeter tile then you're out!
bool isPositionWithinPerimeter(const Position& pos, const Position& lowerBound, const Position& upperBound)
{
    // If point has already been seen, return early
    if (allColoredTiles.contains(pos))
        return true;

    if (allEmptyTiles.contains(pos))
        return false;

    // If not, confirm that we are within the bounds
    assert(pos.x >= lowerBound.x && pos.y >= lowerBound.y);
    assert(pos.x <= upperBound.x && pos.y <= upperBound.y);


    Position posIncreasingX = pos;
    while (true)
    {
        if (allColoredTiles.contains(posIncreasingX))
            break;
        if (posIncreasingX.x == upperBound.x)
        {
            allEmptyTiles.insert(pos);
            return false;
        }
        ++posIncreasingX.x;
    }


    Position posIncreasingY = pos;
    while (true)
    {
        if (allColoredTiles.contains(posIncreasingY))
            break;
        if (posIncreasingY.y == upperBound.y)
        {
            allEmptyTiles.insert(pos);
            return false;
        }
        ++posIncreasingY.y;
    }

    Position posDecreasingX = pos;
    while (true)
    {
        if (allColoredTiles.contains(posDecreasingX))
            break;
        if (posDecreasingX.x == lowerBound.x)
        {
            allEmptyTiles.insert(pos);
            return false;
        }
        --posDecreasingX.x;
    }

    Position posDecreasingY = pos;
    while (true)
    {
        if (allColoredTiles.contains(posDecreasingY))
            break;
        if (posDecreasingY.y == lowerBound.y)
        {
            allEmptyTiles.insert(pos);
            return false;
        }

        --posDecreasingY.y;
    }

    allColoredTiles.insert(pos);
    return true;

}
Position lowerBound;
Position upperBound;
struct Rectangle {

    PositionSet getAllPositionsWithinRectangle()
    {
        PositionSet positions;
        const int64 startX = std::min(p1.x, p2.x);
        const int64 endX = std::max(p1.x, p2.x);
        const int64 startY = std::min(p1.y, p2.y);
        const int64 endY = std::max(p1.y, p2.y);

        for (int64 x = startX; x <= endX; ++x)
        {
            for (int64 y = startY; y <= endY; ++y)
            {
                positions.insert({ x, y });
            }
        }
        return positions;
    }

    const std::vector<Position> getAllVertices()
    {
        std::vector<Position> outPositions;

        if (p1.x == p2.x || p1.y == p2.y)
        {
            outPositions.emplace_back(p1);
            outPositions.emplace_back(p2);
            return outPositions;
        }

        outPositions.emplace_back(p1);

        Position p3 = p1;
        p3.x = p2.x;

        outPositions.emplace_back(p3);
        outPositions.emplace_back(p2);

        Position p4 = p1;
        p4.y = p2.y;

        outPositions.emplace_back(p4);

        return outPositions;
    }

    bool isWithinPerimeter(const std::vector<Position>& cornerPositions, const PositionSet& perimeterTilePositions)
    {
        for (const auto& pos : getPerimeterPositions(vertices))
            //for (const auto& pos : getAllPositionsWithinRectangle(r))
        {
            if (!isPositionWithinPerimeter(pos, lowerBound, upperBound))
                return false;
        }
        return true;
    }
    Rectangle(const Position& inp1, const Position& inp2) :
        p1(inp1),
        p2(inp2)
    {

        const int64 dX = std::abs(p1.x - p2.x) + TILE_WIDTH;
        const int64 dY = std::abs(p1.y - p2.y) + TILE_WIDTH;

        area = dX * dY;
        vertices = getAllVertices();
    }

    void checkCorners(PositionSet& outside) {
        for (const auto& vertex : vertices) {
            if (outside.contains(vertex)) {
                hasCornerOutside = true;
                return;
            }
        }
    }
    Position p1;
    Position p2;
    int64 area;
    std::vector<Position> vertices;
    bool hasCornerOutside = false;
};

void getBounds(const std::vector<Position>& cornerTilePositions, Position& outPosMin, Position& outPosMax)
{
    outPosMin.x = std::numeric_limits<int64>::max();
    outPosMin.y = std::numeric_limits<int64>::max();
    outPosMax.x = -std::numeric_limits<int64>::max();
    outPosMax.y = -std::numeric_limits<int64>::max();

    for (int iCorner = 0; iCorner < cornerTilePositions.size(); ++iCorner)
    {
        const Position& cornerPos = cornerTilePositions[iCorner];
        if (cornerPos.x > outPosMax.x)
        {
            outPosMax.x = cornerPos.x;
        }
        if (cornerPos.y > outPosMax.y)
        {
            outPosMax.y = cornerPos.y;
        }
        if (cornerPos.x < outPosMin.x)
        {
            outPosMin.x = cornerPos.x;
        }
        if (cornerPos.y < outPosMin.y)
        {
            outPosMin.y = cornerPos.y;
        }
    }
}


int64 getMaxArea(const std::vector<Position>& cornerPositions, const PositionSet& perimeterTilePositions)
{
    // get all rectangles
    std::vector<Rectangle> rectangles;
    for (int i = 0; i < cornerPositions.size(); ++i)
    {
        for (int j = i + 1; j < cornerPositions.size(); ++j)
        {
            rectangles.emplace_back(Rectangle(cornerPositions[i], cornerPositions[j]));
        }
    }
    // Sort them by size
    std::sort(rectangles.begin(), rectangles.end(),
        [](const Rectangle& a, const Rectangle& b) {
            return a.area > b.area;
        });

    for (auto& rect : rectangles)
    {
        rect.checkCorners(allEmptyTiles);
#ifdef PART_2
        if (rect.hasCornerOutside)
            continue;
        if (!rect.isWithinPerimeter(cornerPositions, perimeterTilePositions))
            continue;
#endif
        return rect.area;
    }
    return -1;
}


void parseInput(std::ifstream& file, std::vector<Position>& cornerTilePositions)
{
    std::string line;

    while (std::getline(file, line))
    {
        auto commaPos = line.find(',');
        long long x = std::stoll(line.substr(0, commaPos));
        long long y = std::stoll(line.substr(commaPos + 1));

        cornerTilePositions.emplace_back(x, y);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string filename = argv[1];

    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Failed to open file: " << filename << '\n';
        return 1;
    }

    std::vector<Position> cornerTilePositions;

    parseInput(file, cornerTilePositions);

    const PositionSet perimeterTilePositions = getPerimeterPositions(cornerTilePositions);
    allColoredTiles.insert(perimeterTilePositions.begin(), perimeterTilePositions.end());
    getBounds(cornerTilePositions, lowerBound, upperBound);

    const int64 maxArea = getMaxArea(cornerTilePositions, perimeterTilePositions);

    std::cout << "Largest rectangle: " << maxArea << ".\n";
    return 0;
}