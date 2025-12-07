import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.List;
import java.util.function.Function;
import java.util.function.BiFunction;

void main() throws Exception {
	System.out.println("Part 1: " + ((Function<String[], Long>) (input -> Arrays.stream(input[1].split("\\n")).filter(n -> Arrays.stream(input[0].split("\n")).filter(s -> Long.parseLong(s.split("-")[0]) <= Long.parseLong(n) && Long.parseLong(s.split("-")[1]) >= Long.parseLong(n)).count() > 0L).count())).apply(Files.readString(Path.of("input.txt")).split("\\n\\n")));
	System.out.println("Part 2: " + ((BiFunction<List<Long>, Long[], Long>) ((input, data) -> input.stream().mapToLong(n -> n > 0L ? (data[0]++ == 0 ? -n : 0) : (--data[0] == 0 ? -n+1 : 0)).sum())).apply(Arrays.stream(Files.readString(Path.of("input.txt")).split("\\n\\n")[0].split("\\n")).flatMap(s -> Arrays.stream(new String[]{s.substring(0, s.indexOf("-")), s.substring(s.indexOf("-"))}).map(Long::parseLong)).sorted().sorted((a, b) -> Long.compare(Math.abs(b), Math.abs(a))).toList().reversed(), new Long[]{0L}));
}
