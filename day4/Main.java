import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.function.Function;
import java.util.stream.IntStream;

public class Main {
	public static void main(String args[]) throws Exception {
		System.out.println(((Function<char[][], Integer>) (input -> IntStream.range(0, input.length * input[0].length).mapToObj(i -> new int[]{i/input[0].length, i%input[0].length}).mapToInt(i -> input[i[0]][i[1]] == '@' && Arrays.stream(new int[][]{ {1,1}, {1,0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1} }).mapToInt(a -> a[0] + i[0] >= 0 && a[1] + i[1] >= 0 && a[0] + i[0] < input.length && a[1] + i[1] < input[0].length && input[a[0] + i[0]][a[1] + i[1]] == '@' ? 1 : 0).sum() < 4 ? 1 : 0).sum())).apply( Files.lines(Path.of("input.txt")).map(String::toCharArray).toArray(char[][]::new)));
	}
}
