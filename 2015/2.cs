using System;
using System.IO;
using System.Text;


namespace _2
{
    class Solution
    {
        static void Main(string[] args)
        {
            uint area = 0, length = 0;
            StreamReader sr = new StreamReader("inputs/2.txt");

            do
            {
                string line = sr.ReadLine();
                string[] numbers = line.Split('x');
                uint[] myNumbers = { 0, 0, 0 };
                for (int i = 0; i < 3; i++)
                {
                    myNumbers[i] = Convert.ToUInt32(numbers[i]);
                }
                Array.Sort(myNumbers);  
                area += 3 * myNumbers[0] * myNumbers[1] + 2 * myNumbers[1] * myNumbers[2] + 2 * myNumbers[0] * myNumbers[2];	
				length += myNumbers[0] * myNumbers[1] * myNumbers[2] + 2 * myNumbers[0] + 2*myNumbers[1];  


            }
			
            while (!sr.EndOfStream);
            Console.WriteLine("The area: {0}",area);
			Console.WriteLine("The length: {0}", length);
            Console.ReadLine();
            
        }
    }
}
