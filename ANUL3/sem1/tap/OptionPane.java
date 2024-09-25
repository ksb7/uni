import javax.swing.JOptionPane;

public class OptionPane
{
	public static void main(String[] args)
	{
		String sir = JOptionPane.showInputDialog("Sirul:");
		
		String[] cuvinte = sir.split(" ");
		
		for(String cuvant : cuvinte)
		{
			System.out.println(cuvant);			
		}
		
	}
}