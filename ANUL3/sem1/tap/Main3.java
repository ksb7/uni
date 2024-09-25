import java.util.Scanner;

class Time {
    int hour;
    int minute;
    int second;
    
    public Time()
    {
    	this.hour = 0;
    	this.minute = 0;
    	this.second = 0;
    }

    public Time(int hour, int minute, int second) 
    {
        this.hour = hour;
        this.minute = minute;
        this.second = second;
    }

    public String toString() 
    {
        return "Ora introdusa:" + String.format("%02d:%02d:%02d", hour, minute, second);
    }

    public int getHour() {
        return hour;
    }

    public void setHour(int hour) {
        this.hour = hour;
    }
}

class MyTime extends Time 
{
    public MyTime(int hour, int minute, int second) 
    {
        super(hour, minute, second);
    }

    private String getTimeOfDay() 
    {
        if (hour >= 5 && hour < 12) 
        {
            return "dimineata";
        } else if (hour >= 12 && hour < 18) 
        {
            return "amiaza";
        } else if (hour >= 18 && hour < 22) 
        {
            return "seara";
        } else 
        {
            return "noaptea";
        }
    }

    @Override
    public String toString() 
    {
        return super.toString() + "\nEste "+ getTimeOfDay();
    }
}

public class Main3
{
    public static void main(String[] args) 
    {
        try (Scanner in = new Scanner(System.in)) {
			System.out.println("Introduceti ora: ");
			int hour = in.nextInt();
			System.out.println("Introduceti minutele: ");
			int minute = in.nextInt();
			System.out.println("Introduceti secundele: ");
			int second = in.nextInt();

			MyTime time = new MyTime(hour, minute, second);
			System.out.println(time);
		}
    }
}
