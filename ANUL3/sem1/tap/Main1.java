//În fiecare cuvânt din textul dat simbolul de pe poziţia indicată a 
//cuvântului de înlocuit cu un simbol dat. Dacă poziţia indicată este mai mare ca lungimea  cuvântului, corecţia nu se face. 

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main1
{
	public static void main(String[] args)
	{
		InputStreamReader is = new InputStreamReader(System.in);
		BufferedReader bis = new BufferedReader(is);
		try 
		{
			System.out.println("Introdu propozitia: ");
			String buffer = bis.readLine();
			
			System.out.println("Introdu pozitia");
			int pos = Integer.parseInt(bis.readLine());
			
			System.out.println("Caracterul cu care sa se inlocuiasca: ");
			char ch = bis.readLine().charAt(0);
			
			String[] sentences = buffer.split(" ");
			
			for(String sentence : sentences) //pentru toate cuvintele din lista
			{
				StringBuffer newBuffer = new StringBuffer(sentence); //creaza un nou buffer 
				
				if(pos < newBuffer.length()) // verifica daca 
				{
					newBuffer.setCharAt(pos, ch); // modifica la pozitia data
				}
				
				System.out.print(newBuffer + " "); // afiseaza bufferul modificat
			}
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		
	}
}