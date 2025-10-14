//De realizat variantele date  folosind exceptiele.
//    1. Sa se citeasca cite  un rind  dintr-un fişier şi să se înscrie in  stivă. Apoi rîndurile din stivă de înscris  în fişier în ordine inversă.
import java.io.*;
import java.util.*;

public class Main5 
{
	public static void main(String[] args) 
	{
		String inputFile = "input.txt";
		String outputFile = "output.txt";

		Stack<String> stack = new Stack<>();

		try 
		{
			BufferedReader reader = new BufferedReader(
					new FileReader(inputFile));
			String line;

			while ((line = reader.readLine()) != null) // pana randul este gol
			{
				stack.push(line);
			}
			reader.close();

			BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile));
			while (!stack.isEmpty()) 
			{
				writer.write(stack.pop()); // in ordine inversa, datorita principiului FILO
				writer.newLine();
			}
			writer.close();

			System.out.println("Fișierul a fost procesat cu succes!");
		} 
		catch (FileNotFoundException e) 
		{
			System.err.println("Eroare: Fișierul de intrare nu a fost găsit.");
		} 
		catch (IOException e) 
		{
			System.err.println("Eroare la citirea sau scrierea fișierului: " + e.getMessage());
		}
	}
}
