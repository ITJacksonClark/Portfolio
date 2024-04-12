// Part C of the NPC Reduction Programming Assignment
// By Jackson Clark
// 3/8/24

import java.util.*;
import java.io.*;

class findVCover {
    static class VertexCover
    {
        boolean check;

        boolean[] result;

        VertexCover(boolean bool, boolean[] boolArr)
        {
            check = bool;
            result = boolArr;
        }
    }

    static boolean kCheckEquals(int k, boolean[] result, int size)
    {
        int count = 0;
        for(int i = 0; i < size; i++)
        {
            if(result[i] == true)
            {
                count++;
            }
        }
        if(count == k)
        {
            return true;
        }
        return false;
    }

    static boolean isMatrixEqual(int[][] adjMatrix, int[][] visited, int size)
    {
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(adjMatrix[i][j] != visited[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    static void increaseEdges(int[][] visited, int[][] adjMatrix, int curVertex, int size)
    {
        for(int i = 0; i < size; i++)
        {
            visited[curVertex][i] = adjMatrix[curVertex][i];
            visited[i][curVertex] = adjMatrix[i][curVertex];
        }
    }

    static void reset(int size, int[][] adjMatrix, int[][] visited, int curVertex, boolean[] result)
    {
        for(int i = 0; i < size; i++)
        {
            if(curVertex != i)
            {
                if(result[i] == false)
                {
                    visited[curVertex][i] = 0;
                    visited[i][curVertex] = 0;
                }
            }
        }
    }

    static int edgesSetup(int[][] adjMatrix, int edges, int size)
    {
        for(int i = 0; i < size - 1; i++)
        {
            for(int j = i + 1; j < size; j++)
            {
                if(adjMatrix[i][j] == 1)
                {
                    edges = edges + 1;
                }
            }
        }
        return edges;
    }

    static void visitSetup(int[][] visited, int size)
    {
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(i == j)
                {
                    visited[i][j] = 1;
                }
                else
                {
                    visited[i][j] = 0;
                }
            }
        }
    }

    static void resultSetup(boolean[] result, int size)
    {
        for(int i = 0; i < size; i++)
        {
            result[i] = false;
        }
    }

    static VertexCover findVertexCoverRec(int[][] adjMatrix, int k, int curVertex, int[][] visited, boolean[] result, int size)
    {
        if(curVertex != size)
        {
            result[curVertex] = true;
            increaseEdges(visited, adjMatrix, curVertex, size);
        }

        if(isMatrixEqual(adjMatrix, visited, size) == true && kCheckEquals(k, result, size) == true)
        {
            return new VertexCover(true, result);
        }

        if(isMatrixEqual(adjMatrix, visited, size) == false && kCheckEquals(k, result, size) == true)
        {
            return new VertexCover(false, result);
        }

        for(int i = curVertex; i > 0; i--)
        {
            VertexCover vc = findVertexCoverRec(adjMatrix, k, curVertex - 1, visited, result, size);
            if(vc.check == true)
            {
                return vc;
            }
            curVertex--;
            reset(size, adjMatrix, visited, curVertex, result);
            result[curVertex] = false;
        }

        return new VertexCover(false, result);
    }

    static void printVCover(VertexCover vCover, int size, int edges, int k, long duration)
    {
        int check = 0;
        if(vCover.check == true)
        {
            if(size < 10)
            {
                System.out.print("( " + size + ", " + edges + ") (size=" + k + " ms=" + duration + ") {");
            }
            else
            {
                System.out.print("(" + size + ", " + edges + ") (size=" + k + " ms=" + duration + ") {");
            }
            for(int i = 0; i < size; i++)
            {
                if(vCover.result[i] == true)
                {
                    if(check == 0)
                    {
                        System.out.print(i);
                        check++;
                    }
                    else
                    {
                        System.out.print("," + i);
                    }
                }
            }
            System.out.print("}\n");
        }
        else
        {
            System.out.println("No vertex cover for k=" + k + " found.");
        }
    }

    static void findVertexCoverAll(int[][] adjMatrix)
    {
        int size = adjMatrix.length;
        int edges = edgesSetup(adjMatrix, 0, size);
        int visited[][] = new int[size][size];
        visitSetup(visited, size);
        
        boolean[] result = new boolean[size];
        resultSetup(result, size);

        int kCount = 0;
        boolean whileCheck = false;
        long startTime;
        VertexCover vCover;
        long endTime;
        long duration;

        while(whileCheck == false)
        {
            kCount++;

            startTime = System.nanoTime();

            vCover = findVertexCoverRec(adjMatrix, kCount, size, visited, result, size);

            endTime = System.nanoTime();

            duration = (endTime - startTime) / 1000000;

            whileCheck = vCover.check;

            if(vCover.check == true)
            {
                printVCover(vCover, size, edges, kCount, duration);
            }
        }
    }

    static boolean[] findVertexCover(int[][] adjMatrix, int k)
    {
        int size = adjMatrix.length;

        int visited[][] = new int[size][size];
        visitSetup(visited, size);
        
        boolean[] result = new boolean[size];
        resultSetup(result, size);

        VertexCover vCover = findVertexCoverRec(adjMatrix, k, size, visited, result, size);

        if(vCover.check == true)
        {
            return vCover.result;
        }
        return new boolean[0];
    }

    public static void main(String[] args) throws Exception
    {
        String fileName = args[0];
        LinkedList<int[][]> matLL = new LinkedList<int[][]>();
        int[][] adjMatrix;
        int i = 0;
        int j = 0;
        int size;
        int integer;
        int count;
        File file = new File(fileName);
        Scanner read = new Scanner(file);
        size = read.nextInt();
        adjMatrix = new int[size][size];
        count = size * size;
        while(read.hasNext())
        {
            if(read.hasNextInt())
            {
                integer = read.nextInt();
                if(count == 0)
                {
                    i = 0;
                    j = 0;
                    matLL.add(adjMatrix);
                    size = integer;
                    adjMatrix = new int[size][size];
                    count = size * size;
                }
                else
                {
                    if(j == size)
                    {
                        i++;
                        j = 0;
                    }
                    adjMatrix[i][j] = integer;
                    j++;
                    count--;
                }
            }
            else
            {
                read.next();
            }
        }

        System.out.println("* A Minimum Vertex Cover of every graph in "+ fileName + " *");
        System.out.println("   (|V|,|E|) (size, ms used) Vertex Cover");
        for(int q = 0; q < matLL.size(); q++)
        {
            System.out.print("G" + (q + 1) + " ");
            findVertexCoverAll(matLL.get(q));
        }
    }
}