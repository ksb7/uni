import java.util.function.Consumer;

public class ProcessThread extends Thread {
    private int id;
    private int runtime;
    private Synchronization sync;
    private Consumer<String> logger;

    public ProcessThread(int id, int runtime, Synchronization sync, Consumer<String> logger) {
        this.id = id;
        this.runtime = runtime;
        this.sync = sync;
        this.logger = logger;
    }

    @Override
    public void run() {
        sync.requestResource(id);
        log("Procesul " + id + " rulează " + runtime + " ms...");
        try { Thread.sleep(runtime); } catch (InterruptedException e) { e.printStackTrace(); }
        sync.releaseResource(id);
        log("Procesul " + id + " a terminat execuția.\n");
    }

    private void log(String mesaj) {
        if (logger != null) {
            logger.accept(mesaj);
        } else {
            System.out.println(mesaj);
        }
    }
}
