using System;
using System.IO;
using System.Collections.Generic;							 
using System.Text;
					

// uncomment the line 36 to get the result of the second part
namespace _3
{
    class Solution
    {
        static void Main(string[] args)
        {
            List<string> addresses = new List <string>();
            int santaPositionWidth = 0, santaPositionHeight = 0, roboPositionWidth = 0, roboPositionHeight = 0;
            addresses.Add(String.Format("{0}.{1}",0,0));
            StreamReader sr = new StreamReader("inputs/3.txt");
			bool robo = false;
            do
            {   
                char dir = (char)sr.Read(); 
				
				switch(dir)
				{
					case '<': if (robo) roboPositionWidth--; else santaPositionWidth--;  break;
					case '>': if (robo) roboPositionWidth++; else santaPositionWidth++;  break;
					case '^': if (robo) roboPositionHeight--; else santaPositionHeight--; break;
					case 'v': if (robo) roboPositionHeight++; else santaPositionHeight++; break;
				}
				
				string addresse;
                if (robo) 
					addresse = String.Format("{0}.{1}", roboPositionWidth, roboPositionHeight);
				else 
					addresse = String.Format("{0}.{1}",santaPositionWidth, santaPositionHeight);
                //robo = !robo;
				if (!addresses.Contains(addresse)) addresses.Add(addresse);
                                
            }
            while (!sr.EndOfStream);

            Console.WriteLine("Nr of households: {0}",addresses.Count);
            Console.ReadLine();

        }
    }
}
