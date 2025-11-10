import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Calendar;

public class Main 
{
    public static void main(String[] args) 
    {

        // Timer care reactioneaza după un anumit interval (2 sec)
        Timer timerDelay = new Timer();
        timerDelay.schedule(new TimerTask() 
        {
            @Override
            public void run() 
            {
                System.out.println("Task 1: Eecutat după 2 secunde");
            }
        }, 2000); // delay în milisecunde


        // Timer care reactioneaza la un anumit timp indicat
        Calendar calendar = Calendar.getInstance();
        calendar.add(Calendar.SECOND, 5); // ruleaza peste 5 secunde de la inceputul executarii
        Date timeToRun = calendar.getTime();

        Timer timerAtTime = new Timer();
        timerAtTime.schedule(new TimerTask() 
        {
            @Override
            public void run() 
            {
                System.out.println("Task 2: Executat la timpul indicat");
            }
        }, timeToRun);


        // 3. Timer care reactioneaza periodic (la fiecare 3 secunde)
        Timer timerPeriodic = new Timer();
        timerPeriodic.scheduleAtFixedRate(new TimerTask() 
        {
            @Override
            public void run() 
            {
                System.out.println("Task 3: Se executa la fiecare 3 secunde");
            }
        }, 0, 3000); // start imediat, perioada 3 secunde
    }
}
