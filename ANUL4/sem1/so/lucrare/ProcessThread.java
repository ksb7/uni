public class ProcessThread extends Thread 
{
    private int id;
    private int runtime;
    private Synchronization sync;

    public ProcessThread(int id, int runtime, Synchronization sync) 
    {
        this.id = id;
        this.runtime = runtime;
        this.sync = sync;
    }

    @Override
    public void run() 
    {
        sync.requestResource(id);
        System.out.println("Procesul " + id + " rulează " + runtime + " ms...");
        try {
            Thread.sleep(runtime);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        sync.releaseResource(id);
        System.out.println("Procesul " + id + " a terminat execuția.\n");
    }
}
