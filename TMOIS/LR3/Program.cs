using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static List<T> Intersect<T>(List<T> A, List<T> B) =>
        A.Where(B.Contains).ToList();

    static List<T> Union<T>(List<T> A, List<T> B)
    {
        var res = new List<T>(A);
        foreach (var b in B)
            if (!res.Contains(b))
                res.Add(b);
        return res;
    }

    static List<T> Subtract<T>(List<T> A, List<T> B) =>
        A.Where(x => !B.Contains(x)).ToList();

    static bool Equal<T>(List<T> A, List<T> B)
    {
        if (A.Count != B.Count) return false;
        return A.All(B.Contains) && B.All(A.Contains);
    }

    static List<(T, T)> Invert<T>(List<(T, T)> g) =>
        g.Select(p => (p.Item2, p.Item1)).Distinct().ToList();

    static List<(T, T)> Compose<T>(List<(T, T)> g1, List<(T, T)> g2)
    {
        var result = new List<(T, T)>();

        foreach (var p1 in g1)
            foreach (var p2 in g2)
                if (Equals(p1.Item2, p2.Item1))
                    result.Add((p1.Item1, p2.Item2));

        return result.Distinct().ToList();
    }

    static List<T> Image<T>(List<(T, T)> g, List<T> set) =>
        g.Where(p => set.Contains(p.Item1))
         .Select(p => p.Item2)
         .Distinct()
         .ToList();

    static List<T> Preimage<T>(List<(T, T)> g, List<T> set) =>
        g.Where(p => set.Contains(p.Item2))
         .Select(p => p.Item1)
         .Distinct()
         .ToList();

    static List<string> InputSet(string name)
    {
        Console.WriteLine($"Enter elements of set {name} separated by spaces:");
        var input = Console.ReadLine()!;
        return input.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
                   .Select(x => x.Trim())
                   .Where(x => !string.IsNullOrEmpty(x))
                   .ToList();
    }

    static List<(string, string)> InputGraph(string setNameX, string setNameY)
    {
        Console.WriteLine($"Enter relation pairs between {setNameX} and {setNameY} (each pair in 'a b' format, one pair per line). Press Enter on an empty line to finish:");
        
        var g = new List<(string, string)>();
        
        while (true)
        {
            var input = Console.ReadLine()?.Trim();
            if (string.IsNullOrEmpty(input))
                break;
            
            var p = input.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            if (p.Length == 2)
            {
                g.Add((p[0], p[1]));
            }
            else
            {
                Console.WriteLine("Error: enter a pair in 'a b' format");
            }
        }
        
        return g;
    }

    static List<(string, string)> InputGraphFromString(string name)
    {
        Console.WriteLine($"Enter relation pairs for {name} (each pair in 'a b' format, one pair per line). Press Enter on an empty line to finish:");
        
        var g = new List<(string, string)>();
        
        while (true)
        {
            var input = Console.ReadLine()?.Trim();
            if (string.IsNullOrEmpty(input))
                break;
            
            var p = input.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            if (p.Length == 2)
            {
                g.Add((p[0], p[1]));
            }
            else
            {
                Console.WriteLine("Error: enter a pair in 'a b' format");
            }
        }
        
        return g;
    }

    static void PrintSet(string name, List<string> set)
    {
        Console.Write($"{name} = {{ ");
        Console.Write(string.Join(", ", set));
        Console.WriteLine(" }");
    }

    static void PrintGraph(string name, List<(string, string)> graph)
    {
        if (graph.Count == 0)
        {
            Console.WriteLine($"{name} = {{ }}");
            return;
        }

        Console.Write($"{name} = {{ ");
        Console.Write(string.Join(", ", graph.Select(p => $"({p.Item1},{p.Item2})")));
        Console.WriteLine(" }");
    }

    static void Main()
    {
        Console.WriteLine("Input sets and relations\n");

        var H = InputGraphFromString("H");
        
        var X = InputSet("X");
        var Y = InputSet("Y");
        var G = InputGraph("X", "Y");

        Console.WriteLine("\nInitial data");
        PrintGraph("H", H);
        PrintSet("X", X);
        PrintSet("Y", Y);
        PrintGraph("G", G);

        Console.WriteLine("\n All operations \n");

        Console.WriteLine("1. Union of G and H");
        var unionGH = Union(G, H);
        PrintGraph("G U H", unionGH);
        Console.WriteLine();

        Console.WriteLine("2. Intersection of G and H ");
        var intersectGH = Intersect(G, H);
        PrintGraph("G ∩ H", intersectGH);
        Console.WriteLine();

        Console.WriteLine("3. Difference of G and H");
        var subtractGH = Subtract(G, H);
        PrintGraph("G \\ H", subtractGH);
        Console.WriteLine();

        Console.WriteLine("4. Difference of H and G");
        var subtractHG = Subtract(H, G);
        PrintGraph("H \\ G", subtractHG);
        Console.WriteLine();

        Console.WriteLine("5. Inversion of relation G^-1");
        var invertedG = Invert(G);
        PrintGraph("G^-1", invertedG);
        Console.WriteLine();

        Console.WriteLine("6. Inversion of relation H^-1");
        var invertedH = Invert(H);
        PrintGraph("H^-1", invertedH);
        Console.WriteLine();

        Console.WriteLine("7. Composition of G and H");
        var compositionGH = Compose(G, H);
        PrintGraph("G ∘ H", compositionGH);
        Console.WriteLine();

        Console.WriteLine("8. Composition of H and G");
        var compositionHG = Compose(H, G);
        PrintGraph("H ∘ G", compositionHG);
        Console.WriteLine();

        Console.WriteLine("\n14. Operations with subsets");
        
        Console.WriteLine("Enter subset A of set X (elements separated by spaces):");
        var A = InputSet("A");
        
        var imageA_G = Image(G, A);
        Console.Write("Image of set A through G: ");
        PrintSet("Γ_G(A)", imageA_G);

        Console.WriteLine("Enter subset B of set Y (elements separated by spaces):");
        var B = InputSet("B");
        
        var preimageB_G = Preimage(G, B);
        Console.Write("Preimage of set B through G: ");
        PrintSet("Γ_G^-1(B)", preimageB_G);
    }
}