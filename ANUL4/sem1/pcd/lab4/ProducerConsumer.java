import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class ProducerConsumer 
{

    public static final int X = 3; // nr. producatori
    public static final int Y = 3; // nr. consumatori
    public static final int Z = 5; // obiecte per consumator
    public static final int D = 6; // capacitate depozit
    private static final char[] VOCALE = {'A', 'E', 'I', 'O', 'U'};

    public static void main(String[] args) 
    {
        Depot depot = new Depot(D, Y * Z); // total obiecte de consumat

        // Producatori
        for (int i = 1; i <= X; i++) 
        {
            int id = i;
            new Thread(() -> 
            {
                Random rand = new Random();
                while (true) 
                {
                    char obj1 = VOCALE[rand.nextInt(VOCALE.length)];
                    char obj2 = VOCALE[rand.nextInt(VOCALE.length)];
                    if (!depot.produce("Producator " + id, obj1, obj2)) break;
                    try { Thread.sleep(100); } catch (InterruptedException e) {}
                }
            }, "Producator-" + i).start();
        }

        // Consumatori
        for (int i = 1; i <= Y; i++) 
        {
            int id = i;
            new Thread(() -> 
            {
                int consumed = 0;
                while (consumed < Z) 
                {
                    char obj = depot.consume("Consumator " + id);
                    if (obj != 0) consumed++;
                    try { Thread.sleep(150); } catch (InterruptedException e) {}
                }
            }, "Consumator-" + i).start();
        }
    }
}

class Depot 
{
    private final List<Character> buffer = new LinkedList<>();
    private final int capacity;
    private int totalConsumed = 0;
    private final int totalToConsume;

    public Depot(int capacity, int totalToConsume) 
    {
        this.capacity = capacity;
        this.totalToConsume = totalToConsume;
    }

    // Returneaza false daca nu mai trebuie sa produca
    public synchronized boolean produce(String producerName, char obj1, char obj2) 
    {
        while (buffer.size() + 2 > capacity && totalConsumed < totalToConsume) 
        {
            System.out.println(producerName + ": Depozit plin, astept...");
            try { wait(); } catch (InterruptedException e) {}
        }
        if (totalConsumed >= totalToConsume) {
            notifyAll();
            return false; // iese din thread
        }
        buffer.add(obj1);
        buffer.add(obj2);
        System.out.println(producerName + " a produs: " + obj1 + " si " + obj2);
        notifyAll();
        return true;
    }

    public synchronized char consume(String consumerName)
    {
        while (buffer.isEmpty()) 
        {
            if (totalConsumed >= totalToConsume) return 0;
            System.out.println(consumerName + ": Depozit gol, astept...");
            try { wait(); } catch (InterruptedException e) {}
        }
        char obj = buffer.remove(0);
        totalConsumed++;
        System.out.println(consumerName + " a consumat: " + obj);
        notifyAll();
        return obj;
    }
}
