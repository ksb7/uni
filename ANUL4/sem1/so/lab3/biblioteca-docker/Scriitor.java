public class Scriitor extends Thread 
{
    private Biblioteca biblioteca;
    private int numarCarti;
    private String nume;

    public Scriitor(String nume, Biblioteca biblioteca, int numarCarti) 
    {
        this.nume = nume;
        this.biblioteca = biblioteca;
        this.numarCarti = numarCarti;
    }

    @Override
    public void run() 
    {
        for (int i = 1; i <= numarCarti; i++) 
        {
            biblioteca.adaugaCarte(nume + "_Cartea_" + i);
            try { Thread.sleep(50); } catch (InterruptedException e) {}
        }
        biblioteca.scriitorTerminat(); // semnaleaza ca a terminat
    }
}
