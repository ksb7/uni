class SubClass1
{
	int i;
	float j;
	SubClass1() 
	{
		i = 3;
		j = 40;
	}
	SubClass1(int a, float b)
	{
		this.i = a;
		this.j = b;
	}
	SubClass1(int res)
	{
		this.i = res;
		this.j = (float) 3.5;
	}
	
	float product()
	{
		return i * j;
	}
	
	void print()
	{
		System.out.println("i = " + i + " j = " + j + " i * j = " + product());
	}
	
	float sum()
	{
		return i + j;
	}
	
}

public class SubClass extends SubClass1
{
	int a;
	float b;
	
	public SubClass()
	{
		super();
	}
	
	public SubClass(int a, float b)
	{
		super(a, b);
	}
	
	public SubClass(int res)
	{
		super(res);
		this.b = (float) 54.3;
	}
	
	public float product()
	{
		return a * b + 100;
	}
	
	void print()
	{
		super.print();
		System.out.println("a*b = " + product());
	}
	
	public static void main(String[] args)
	{
		
		SubClass nr1 = new SubClass();
		SubClass nr2 = new SubClass(1, (float) 3.4);
		SubClass nr3 = new SubClass(2);
		
		nr1.print();
		nr2.print();
		nr3.print();
		
		System.out.println(nr3.sum());
		
	}
}
