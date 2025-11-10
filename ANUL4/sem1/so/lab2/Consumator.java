public class Consumator extends Thread 
{
    private final Depozit depozit;
    private final int id;

    public Consumator(Depozit d, int id) 
    {
        this.depozit = d;
        this.id = id;
    }

    @Override
    public void run() 
    {
        try {
            while (depozit.consumateTotale < depozit.Z) 
            {
                depozit.consume(id);
                Thread.sleep(250);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
