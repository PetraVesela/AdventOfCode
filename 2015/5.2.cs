using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text.RegularExpressions;

namespace _10
{
    class Program
    {
 
        static void Main(string[] args)
        {
            int nice = 0;
            int naughty = 0;
            StreamReader sr = new StreamReader("inputs/2.txt");
            Regex pattern1 = new Regex(@"(\w).\1{1,}");      //xyx, aoa
            
            
            do
            {
                bool druhaPodminka = false;
            navesti:
                string radek = sr.ReadLine();
                string[] seznamDvojic = { "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0" };
                
                for (int i = 0; i < 15; i++)
                {
                    seznamDvojic[i] = String.Format("{0}{1}", radek[i], radek[i + 1]);
                }

                string[] seznamUnikatnich = { "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0" };
                Dictionary<int, int> dvojice = new Dictionary<int, int>();
                for (int i = 0; i<15;i++)
                {
                    if (!seznamUnikatnich.Contains(seznamDvojic[i]))
                        seznamUnikatnich[i] = seznamDvojic[i];
                    else 
                    {
                        

                        for (int a = 0; a<i;a++)
                        {
                            if ((seznamDvojic[i] == seznamDvojic[a]))
                            {
                                try { dvojice.Add(a, i); }
                                catch (Exception e)
                                { 
                                    nice++;
                                    goto navesti;
                                }
                                                        //zjisteni indexů s duplikáty, a = první, i = druhý výskyt;
                                continue;               //JE HORŠÍ NECHAT NĚKOLIK CYKLŮ NAPRÁZDNO, NEBO POUŽÍT GOTO pro skok mezi fory?
                            }
                                                         
                        }
                        
                    } 
                    
                }

               foreach (int klic in dvojice.Keys)
               {
                   if ((dvojice[klic] - klic >1))
                       druhaPodminka = true;

               }

               if (druhaPodminka && pattern1.IsMatch(radek))
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
