//Realizarea polimorfismului pentru clasele date cu crearea metodelor conform specificului claselor.
//1.      Fraction <- ComplexFracion.

import java.util.Scanner;

class Fraction 
{
    protected int numarator;
    protected int numitor;

    public Fraction(int numarator, int numitor) 
    {
        if (numitor == 0) {
            throw new IllegalArgumentException("Numitorul nu poate fi 0");
        }
        this.numarator = numarator;
        this.numitor = numitor;
    }

    public void display() 
    {
        System.out.println(numarator + "/" + numitor);
    }

    public double value() 
    {
        return (double) numarator / numitor;
    }
}

class ComplexFraction extends Fraction 
{
    private int numaratorImg;
    private int numitorImg;

    public ComplexFraction(int realnumarator, int realnumitor, int numaratorImg, int numitorImg) 
    {
        super(realnumarator, realnumitor);
        this.numaratorImg = numaratorImg;
        this.numitorImg = numitorImg;
    }

    @Override
    public void display() 
    {
        String realPart = numarator + "/" + numitor;
        String imaginaryPart = numaratorImg + "/" + numitorImg + "i";
        System.out.println(realPart + " + " + imaginaryPart);
    }

    @Override
    public double value() 
    {
        return super.value(); 
    }
}

public class Main4 
{
    public static void main(String[] args) 
    {
    	System.out.println("Numaratorul si numitorul: ");
    	try (Scanner in = new Scanner(System.in)) {
			int numarator = in.nextInt();
			int numitor = in.nextInt();
			
			Fraction fraction = new Fraction(numarator, numitor);
			fraction.display(); 
			System.out.println("Valoarea calculata: " + fraction.value()); 
			
			System.out.println("Numaratorul si numitorul (real si imaginar respectiv): ");
			int numaratorReal = in.nextInt();
			int numitorReal = in.nextInt();
			int numaratorImg = in.nextInt();
			int numitorImg = in.nextInt();

			Fraction complexFraction = new ComplexFraction(numaratorReal, numitorReal, numaratorImg, numitorImg);
			complexFraction.display();
			System.out.println("Valoarea calculata: " + complexFraction.value());
		} 
    }
}
