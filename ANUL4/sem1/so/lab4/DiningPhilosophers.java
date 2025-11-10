import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

class Chopstick 
{
    private boolean taken = false;

    // metoda sincronizata pentru a lua betisorul
    public synchronized void pickUp() throws InterruptedException 
    {
        while (taken) {
            wait();
        }
        taken = true;
    }

    // metoda sincronizata pentru a elibera betisorul
    public synchronized void putDown() 
    {
        taken = false;
        notifyAll();
    }
}

class Philosopher extends Thread 
{
    private int id;
    private Chopstick left;
    private Chopstick right;
    private int eatCount = 0;
    private int maxMeals;
    private PrintWriter log;

    public Philosopher(int id, Chopstick left, Chopstick right, int maxMeals, PrintWriter log) 
    {
        this.id = id;
        this.left = left;
        this.right = right;
        this.maxMeals = maxMeals;
        this.log = log;
    }

    private void think() throws InterruptedException 
    {
        log.println("Philosopher " + id + " is thinking.");
        Thread.sleep(new Random().nextInt(500));
    }

    private void eat() throws InterruptedException 
    {
        log.println("Philosopher " + id + " starts eating.");
        Thread.sleep(new Random().nextInt(500));
        log.println("Philosopher " + id + " finishes eating.");
        eatCount++;
    }

    @Override
    public void run() 
    {
        try 
        {
            while (eatCount < maxMeals) 
            {
                think();
                
                // Filosofii iau betisoarele in ordine diferita pentru a evita deadlock
                if (id % 2 == 0) 
                {
                    left.pickUp();
                    right.pickUp();
                } else 
                {
                    right.pickUp();
                    left.pickUp();
                }

                eat();

                left.putDown();
                right.putDown();
            }
            log.println("Philosopher " + id + " has finished all meals.");
        } catch (InterruptedException e) 
        {
            Thread.currentThread().interrupt();
        }
    }
}

public class DiningPhilosophers 
{
    public static void main(String[] args) 
    {
        int groupSize = 7;
        int n = groupSize + 6; // n filosofi

        Chopstick[] chopsticks = new Chopstick[n];
        for (int i = 0; i < n; i++) 
        {
            chopsticks[i] = new Chopstick();
        }

        try (PrintWriter log = new PrintWriter(new FileWriter("philosophers.log"))) 
        {
            Philosopher[] philosophers = new Philosopher[n];
            int maxMeals = 3; // fiecare filosof mănâncă de 3 ori
            
            for (int i = 0; i < n; i++) 
            {
                Chopstick left = chopsticks[i];
                Chopstick right = chopsticks[(i + 1) % n];
                philosophers[i] = new Philosopher(i, left, right, maxMeals, log);
                philosophers[i].start();
            }

            // asteptam terminarea tuturor filosofilor
            for (int i = 0; i < n; i++) 
            {
                philosophers[i].join();
            }

            log.println("All philosophers have finished eating.");
        } catch (IOException | InterruptedException e) 
        {
            e.printStackTrace();
        }
    }
}
