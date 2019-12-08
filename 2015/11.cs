using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text.RegularExpressions;

namespace _11
{
    class Program
    {
        public static void increase(byte[] input, int index)
        {
            if (input[index] == 122) {
                input[index] = 97;
                increase(input, index - 1); 
            } 
            else {
                input[index]++; 
			}			
        }
        
        static void Main(string[] args)
        {

            string input = "hxbxxyzz";
            bool allConditions = false;
            Regex pattern1 = new Regex("abc|bcd|cde|def|efg|fgh|pqr|qrs|rst|stu|tuv|uvw|vwx|wxy|xyz");
            Regex pattern2 = new Regex(@"(\w)\1{1}.?(\w)\2{1}");
            
            do
            {
                byte[] asciiBytes = Encoding.ASCII.GetBytes(input);
                increase(asciiBytes, 7);
                input = Encoding.ASCII.GetString(asciiBytes);
                Console.WriteLine(input);
                
                if (!Regex.IsMatch(input, "(i|o|l)") && pattern1.IsMatch(input) && pattern2.IsMatch(input))
                    allConditions = true;
                
            }
            while (allConditions == false);
            Console.WriteLine(input);
            Console.ReadLine();

        }
    }
}
