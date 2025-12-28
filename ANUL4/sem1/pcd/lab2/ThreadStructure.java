public class ThreadStructure {
    public static void main(String[] args) 
    {

        ThreadGroup mainGroup = Thread.currentThread().getThreadGroup();

        // Runnable care tine firul în viata pentru 2 secunde
        Runnable hold = () -> 
        {
            try 
            {
                Thread.sleep(2000);
            } catch (InterruptedException e) {}
        };

        // 1) ThA(3)
        Thread thA = new Thread(mainGroup, hold, "ThA");
        thA.setPriority(3);

        // 2) Grupul G2
        ThreadGroup G2 = new ThreadGroup(mainGroup, "G2");

        Thread Th1 = new Thread(G2, hold, "Th1");  Th1.setPriority(5);
        Thread Th2 = new Thread(G2, hold, "Th2");  Th2.setPriority(3);
        Thread Th33 = new Thread(G2, hold, "Th33"); Th33.setPriority(7);

        // 3) Th11, Th22 în main
        Thread Th11 = new Thread(mainGroup, hold, "Th11"); Th11.setPriority(3);
        Thread Th22 = new Thread(mainGroup, hold, "Th22"); Th22.setPriority(3);

        // 4) G1 -> G3
        ThreadGroup G1 = new ThreadGroup(mainGroup, "G1");
        ThreadGroup G3 = new ThreadGroup(G1, "G3");

        Thread Thaa = new Thread(G3, hold, "Thaa"); Thaa.setPriority(2);
        Thread Thbb = new Thread(G3, hold, "Thbb"); Thbb.setPriority(3);
        Thread Thcc = new Thread(G3, hold, "Thcc"); Thcc.setPriority(8);
        Thread Thdd = new Thread(G3, hold, "Thdd"); Thdd.setPriority(3);

        // Pornim firele
        thA.start();
        Th1.start(); Th2.start(); Th33.start();
        Th11.start(); Th22.start();
        Thaa.start(); Thbb.start(); Thcc.start(); Thdd.start();

        // Aateptam putin ca toate firele sa porneasca
        try { Thread.sleep(100); } catch (Exception e) {}

        // afisam structura
        System.out.println("=== Structura ThreadGroup ===");
        printGroupInfo(mainGroup, "");
    }

    private static void printGroupInfo(ThreadGroup group, String indent) 
    {
        System.out.println(indent + "ThreadGroup: " + group.getName());

        Thread[] threads = new Thread[group.activeCount() * 2];
        int tcount = group.enumerate(threads, false);

        for (int i = 0; i < tcount; i++) 
        {
            Thread t = threads[i];
            System.out.println(indent + "  Thread: " + t.getName() +
                    " (priority=" + t.getPriority() + "), Group=" + t.getThreadGroup().getName());
        }

        ThreadGroup[] groups = new ThreadGroup[group.activeGroupCount() * 2];
        int gcount = group.enumerate(groups, false);

        for (int i = 0; i < gcount; i++) 
        {
            printGroupInfo(groups[i], indent + "  ");
        }
    }
}
