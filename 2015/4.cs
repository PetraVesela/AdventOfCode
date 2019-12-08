using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;
using System.Collections;

class Solution
    {
        static void Main(string[] args)
        {
			
            string key = "ckczppom";		//here is your input
            string output;
            string shortOutput;
            string temp = "000000";
			
            long coef = 0;

            do 
			{
                string input = String.Format(key + "{0}", coef);

                // step 1, calculate MD5 hash from input
                MD5 md5 = System.Security.Cryptography.MD5.Create();
                byte[] inputBytes = System.Text.Encoding.ASCII.GetBytes(input);
                byte[] hash = md5.ComputeHash(inputBytes);

                // step 2, convert byte array to hex string
                StringBuilder sb = new StringBuilder();

                for (uint j = 0; j < 4; j++)
                {
                    sb.Append(hash[j].ToString("x2"));
                }

                output = sb.ToString();
                shortOutput = String.Format("{0}{1}{2}{3}{4}{5}", output[0], output[1], output[2], output[3], output[4], output[5]);
                coef++;
            }
			
            while (!shortOutput.Equals(temp));
			
			Console.WriteLine(--coef);	
            
            Console.ReadLine();
        }
    }

