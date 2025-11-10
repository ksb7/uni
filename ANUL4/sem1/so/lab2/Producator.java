import java.util.Random;

public class Producator extends Thread 
{
    private final Depozit depozit;
    private final int id;
    private final char[] vocale = {'a', 'e', 'i', 'o', 'u'};
    private final Random rnd = new Random();

    public Producator(Depozit d, int id) 
    {
        this.depozit = d;
        this.id = id;
    }

    @Override
    public void run() 
    {
        try 
        {
            while (depozit.produseTotale < depozit.Z) 
            {
                char x = vocale[rnd.nextInt(vocale.length)];
                char y = vocale[rnd.nextInt(vocale.length)];

                depozit.produce(x, y, id);
                Thread.sleep(200);
            }
        } catch (InterruptedException e) 
        {
            e.printStackTrace();
        }
    }
}
