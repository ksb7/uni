import java.util.Scanner;

class HelloWorld
{
	public static void main(String[] args)
	{
		int count = 0;
		Scanner sc = new Scanner(System.in);
		String sirDeCaractere = sc.nextLine();
		
//		for(int i = sirDeCaractere.length() - 1; i >= 0; i++)
//		{
//			System.out.println(sirDeCaractere.charAt(i));
//		}
//		
//		StringBuffer reversed = new StringBuffer(sirDeCaractere);
//		
//		reversed.reverse();
//		
//		System.out.println(reversed);
		
//		String reversed = sirDeCaractere.replace('x', 'a');
		
//		System.out.println(sirDeCaractere);
//		System.out.println(reversed);
		
//		System.out.println(sirDeCaractere.substring(2, 6));
		
		for(int i = 0; i < sirDeCaractere.length(); i++)
		{
			if(sirDeCaractere.charAt(i) == 'a') count++;
		}
		
		System.out.println(count);
	}
}