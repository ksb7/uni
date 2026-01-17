public class Cititor extends Thread 
{
    private Biblioteca biblioteca;
    private int numarCartiDeCitit;
    private String nume;

    public Cititor(String nume, Biblioteca biblioteca, int numarCartiDeCitit) 
    {
        this.nume = nume;
        this.biblioteca = biblioteca;
        this.numarCartiDeCitit = numarCartiDeCitit;
    }

    @Override
    public void run() 
    {
        int citite = 0;
        while (citite < numarCartiDeCitit) 
        {
            String carte = biblioteca.citesteCarte();
            if (carte == null) 
            {
                break; // nu mai sunt carti si nici scriitori
            }
            citite++;
            try { Thread.sleep(20); } catch (InterruptedException e) {}
        }
    }
}
