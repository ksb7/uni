//Pentru toate variantele extindeţi capacităţile clasei de bază dată folosind moştenirea:
//1.Time, astfel încât să se poată deduce timpul zilei: dimineaţă, seară e.t.c

import java.time.LocalTime;

class ExtendedTime 
{
    private LocalTime time;

    public ExtendedTime(int hour, int minute, int second) 
    {
        this.time = LocalTime.of(hour, minute, second);
    }

    public String getPartOfDay() 
    {
        int hour = time.getHour();

        if (hour >= 6 && hour < 12) 
        {
            return "Dimineata";
        } 
        else if (hour >= 12 && hour < 18) 
        {
            return "Pranz";
        } 
        else if (hour >= 18 && hour < 21) 
        {
            return "Seara";
        } 
        else 
        {
            return "Noaptea";
        }
    }

    public void printTimeWithPartOfDay() {
        System.out.println("Ora: " + time);
        System.out.println("Partea zilei: " + getPartOfDay());
    }

}

public class Main3
{
	public static void main(String[] args) {

        ExtendedTime t1 = new ExtendedTime(9, 30, 0);
        t1.printTimeWithPartOfDay();

        ExtendedTime t2 = new ExtendedTime(14, 45, 0);
        t2.printTimeWithPartOfDay();

        ExtendedTime t3 = new ExtendedTime(19, 15, 0);
        t3.printTimeWithPartOfDay();

        ExtendedTime t4 = new ExtendedTime(2, 0, 0);
        t4.printTimeWithPartOfDay();
    }
}
