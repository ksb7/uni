import java.util.function.Consumer;

public class StableState {
    private int[][] max;
    private int[][] allocated;
    private int[] available;
    private Consumer<String> logger;

    public StableState(int processes, int resources, Consumer<String> logger) {
        this.logger = logger;
        max = new int[processes][resources];
        allocated = new int[processes][resources];
        available = new int[resources];

        // valori care duc la stare sigură
        for (int i = 0; i < processes; i++) {
            for (int j = 0; j < resources; j++) {
                max[i][j] = 3;
                allocated[i][j] = 1;
            }
        }
        for (int j = 0; j < resources; j++) {
            available[j] = 3;
        }
    }

    public boolean isSafeState() {
        int p = max.length;
        int r = max[0].length;
        boolean[] finished = new boolean[p];
        int[] work = available.clone();

        int finishedCount = 0;
        while (finishedCount < p) {
            boolean found = false;
            for (int i = 0; i < p; i++) {
                if (!finished[i]) {
                    boolean canFinish = true;
                    for (int j = 0; j < r; j++) {
                        if (max[i][j] - allocated[i][j] > work[j]) {
                            canFinish = false;
                            break;
                        }
                    }
                    if (canFinish) {
                        for (int j = 0; j < r; j++) {
                            work[j] += allocated[i][j];
                        }
                        finished[i] = true;
                        finishedCount++;
                        found = true;
                    }
                }
            }
            if (!found) break;
        }

        return finishedCount == p;
    }

    public void runThreads() {
        Synchronization sync = new Synchronization(3, logger);
        for (int i = 1; i <= 8; i++) {
            new ProcessThread(i, 200 + i * 100, sync, logger).start();
        }
    }
}
