public class TestBiblioteca 
{
    public static void main(String[] args) 
    {
        int varianta = 17;
        int subgrupa = 1;

        int X = varianta + subgrupa; // 18 scriitori
        int Y = varianta * 2;        // 34 cititori
        int Z = varianta + 3;        // 20 carti

        Biblioteca biblioteca = new Biblioteca(X);

        // Scriitori
        for (int i = 1; i <= X; i++) 
        {
            new Scriitor("Scriitor_" + i, biblioteca, Z).start();
        }

        // Cititori
        for (int i = 1; i <= Y; i++) 
        {
            new Cititor("Cititor_" + i, biblioteca, Z).start();
        }
    }
}
