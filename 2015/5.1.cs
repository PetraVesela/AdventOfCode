using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text.RegularExpressions;

namespace _9
{
    class Program
    {
        static void Main(string[] args)
        {
            int nice = 0;
            int naughty = 0;
            StreamReader sr = new StreamReader("inputs/5.txt");
            Regex pattern1 = new Regex("(ab)|(cd)|(pq)|(xy)");  //forbidden pairs
            Regex pattern2 = new Regex(@"(\w)\1{1}");                //a pair of same letters
            Regex pattern3 = new Regex("(.*a.*|.*e.*|.*i.*|.*o.*|.*u.*){3,}"); // vowels
            
            do 
            {
                    string row = sr.ReadLine();                  
                
                if(!pattern1.IsMatch(row) && pattern2.IsMatch(row) && pattern3.IsMatch(row))
                     nice++;
                else naughty++;
            }
            while (!sr.EndOfStream);
            Console.WriteLine(nice);
            Console.WriteLine(naughty);
            Console.ReadLine();
        }
      

    }
}
