public class Program
{
    public static void Main()
    {
        List<int> resultList = new List<int>();
        List<int> unionList = new List<int>();
        List<int> intersectList = new List<int>();

        Console.WriteLine("Enter elements of the first set (separated by spaces): \n");
        List<int> firstList = ReadSetFromConsole();

        Console.WriteLine("Enter elements of the second set (separated by spaces): \n");
        List<int> secondList = ReadSetFromConsole();

        // 1. Union
        Console.Write("Union: ");
        unionList = firstList.Union(secondList).ToList();
        Console.WriteLine(string.Join(" ", unionList));

        // 2. Intersection
        Console.Write("Intersection: ");
        intersectList = firstList.Intersect(secondList).ToList();
        Console.WriteLine(string.Join(" ", intersectList));

        // 3. Difference
        foreach (var element in firstList)
        {
            if (!secondList.Contains(element))
            {
                resultList.Add(element);
            }
        }

        Console.Write("Difference: ");
        Console.WriteLine(string.Join(" ", resultList));
        resultList.Clear();

        // 4. Symmetric difference
        foreach (var element in unionList)
        {
            if (!intersectList.Contains(element))
            {
                resultList.Add(element);
            }
        }

        Console.Write("Symmetric Difference: ");
        Console.WriteLine(string.Join(" ", resultList));
        resultList.Clear();

        // 5. Complement
        Console.Write("Complement (relative to U): ");
        foreach (var element in unionList)
        {
            if (!secondList.Contains(element))
            {
                resultList.Add(element);
            }
        }

        Console.Write("Complement: ");
        Console.WriteLine(string.Join(" ", resultList));
        resultList.Clear();
    }
    
    private static List<int> ReadSetFromConsole()
    {
        bool isInvalidInput = false;
        while (true)
        {
            string input = Console.ReadLine();
            if (string.IsNullOrWhiteSpace(input))
            {
                Console.WriteLine("Enter at least one element:");
                continue;
            }

            string[] elements = input.Split(' ');
            List<int> result = new List<int>();

            foreach (string element in elements)
            {
                if (int.TryParse(element, out int number)) // TryParse - converts to number
                {
                    result.Add(number);
                }
                else
                {
                    Console.WriteLine($"Error: '{element}' is not a number. Try again:");
                    isInvalidInput = true;
                    break;
                }
            }

            if (!isInvalidInput)
            {
                return result; // exit while loop
            }

            isInvalidInput = false;
        }
    }
}