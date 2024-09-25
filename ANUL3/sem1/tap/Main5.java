//De realizat variantele date  folosind exceptiele.
//    1. Sa se citeasca cite  un rind  dintr-un fişier şi să se înscrie in  stivă. Apoi rîndurile din stivă de înscris  în fişier în ordine inversă.

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import java.util.Stack;

public class Main5
{
	public static void main(String[] args)
	{
		try 
		{
			Stack stiva = new Stack();
			
			Scanner reader = new Scanner("file.in");
			while (reader.hasNextLine())
			{
				int digit = reader.nextInt();
				stiva.push(digit);
			}
		}
		catch
		{
			System.out.println("Fisierul introdus nu a fost gasit");
		}
	}	
}