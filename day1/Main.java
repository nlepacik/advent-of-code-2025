import java.nio.file.Files;
import java.nio.file.Path;

public class Main {
    static int dial = 50;
    public static void main(String args[]) throws Exception {
        System.out.println(Files.lines(Path.of("input.txt")).mapToInt(line -> ((dial += (Integer.parseInt(line.substring(1)) * (line.charAt(0) == 'L' ? -1 : 1))) % 100 == 0) ? 1 : 0).sum());
    }
}
