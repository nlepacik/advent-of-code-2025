import java.nio.file.Files;
import java.nio.file.Path;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.stream.IntStream;
import java.util.stream.Stream;

void main() throws Exception {
	System.out.println("Part 1: " + ((BiFunction<Stream<String>, Integer[], Integer>) ((stream, dial) -> stream.mapToInt(line -> ((dial[0] += (Integer.parseInt(line.substring(1)) * (line.charAt(0) == 'L' ? -1 : 1))) % 100 == 0) ? 1 : 0).sum())).apply(Files.lines(Path.of("input.txt")), new Integer[]{50}));
	System.out.println("Part 2: " + ((BiFunction<Stream<String>, Integer[], Integer>) ((stream, dial) -> stream.mapToInt(line -> ((Function<Integer, Integer>) (d -> (int) (line.charAt(0) == 'L' ? IntStream.rangeClosed(d, d + Integer.parseInt(line.substring(1)) - 1) : IntStream.rangeClosed(d - Integer.parseInt(line.substring(1)) + 1, d)).filter(n -> n % 100 == 0).count())).apply(dial[0] += Integer.parseInt(line.substring(1)) * (line.charAt(0) == 'R' ? 1 : -1))).sum())).apply(Files.lines(Path.of("input.txt")), new Integer[]{50}));
}
