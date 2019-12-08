using System;
using System.IO;

namespace _1
{
    class Solution
    {
        static void Main(string[] args)
        {
            int floor = 0, position = 0;
			bool notYet = true;
            StreamReader sr = new StreamReader("inputs/1.txt");
            do
            {
                char a = (char)sr.Read();
                if (a == '(')
					floor++;
				else 
					floor--;
				
				if (floor == -1 && notYet)
				{
					Console.WriteLine("First time at -1: {0}", position);
					notYet = false;
				}
				position++;
            }
            while (!sr.EndOfStream);

            Console.WriteLine("You landed at the floor nr. {0}", floor);
            Console.ReadLine();
        }
    }
}