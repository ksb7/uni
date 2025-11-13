public class Synchronization 
{
    private int available;

    public Synchronization(int available) 
    {
        this.available = available;
    }

    // Cererea unei resurse
    public synchronized void requestResource(int processId) 
    {
        while (available == 0) 
        {
            try 
            {
                System.out.println("Procesul " + processId + " asteapta resurse");
                wait();
            } catch (InterruptedException e) 
            {
                e.printStackTrace();
            }
        }
        available--;
        System.out.println("Procesul " + processId + " a primit o resursa. Resurse libere: " + available);
    }

    // Eliberarea unei resurse
    public synchronized void releaseResource(int processId) 
    {
        available++;
        System.out.println("Procesul " + processId + " a eliberat o resursa. Resurse libere: " + available);
        notifyAll();
    }
}
