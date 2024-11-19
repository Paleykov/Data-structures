#include "Engine.hpp"

Engine::Engine(): adjacencyMatrix(), currentFileName(""), stopProgram(false), fileIisOpen(false), isFileGenerated(false){}

void Engine::findSolutionHK(const std::string taskname)
{
    if(this->adjacencyMatrix.size() > 22)
    {
        std::cout << "This algorithm is not good for more than ~22 cities. Please, use a heuristic. " << std::endl;
        return;
    }

    HeldKarp object(this->adjacencyMatrix);
    object.run();
    object.printResult("Held-Karp");

    if(!this->isFileGenerated)
    object.visualizeSolution(taskname);
    else
    {
        std::cout << "Solution visualization is not supported for generated files since they are randomized and may not represent a real situation. " << std::endl;
    }
}

void Engine::findSolutionBruteForce(const std::string taskname)
{
    if(this->adjacencyMatrix.size() > 12)
    {
        std::cout << "This algorithm is not good for more than ~12 cities. Please, use another algorithm. " << std::endl;
        return;
    }

    BruteForce object(this->adjacencyMatrix);
    object.run();
    object.printResult("BruteForce");
    
    if(!this->isFileGenerated)
    object.visualizeSolution(taskname);
    else
    {
        std::cout << "Solution visualization is not supported for generated files since they are randomized and may not represent a real situation. " << std::endl;
    }
}

void Engine::findSolutionNearestNeighbour(const std::string taskname)
{
    if(this->adjacencyMatrix.size() > 15000)
    {
        std::cout << "This algorithm is not good for more than ~15000 cities. This is the current limit :). " << std::endl;
        return;
    }

    NearestNeighbor object(this->adjacencyMatrix);
    object.run();
    object.printResult("Nearest Neighbour");
    
    if(!this->isFileGenerated)
    object.visualizeSolution(taskname);
    else
    {
        std::cout << "Solution visualization is not supported for generated files since they are randomized and may not represent a real situation. " << std::endl;
    }
}

void Engine::findSolutionTwoOpt(std::vector<int> path, const std::string taskname)
{
    if(this->adjacencyMatrix.size() > 13000)
    {
        std::cout << "This algorithm is not good for more than ~13000 cities. Please try with the Nearest Neighbour algorithm. " << std::endl;
        return;
    }

    TwoOpt object(this->adjacencyMatrix);
    object.run(path);
    object.printResult("TwoOpt");
    
    if(!this->isFileGenerated)
    object.visualizeSolution(taskname);
    else
    {
        std::cout << "Solution visualization is not supported for generated files since they are randomized and may not represent a real situation. " << std::endl;
    }
}

void Engine::createMap(const std::string &fileName) 
{
    if(this->isFileGenerated)
    {
        std::cout << "Map visualization is not supported for generated files since they are randomized and may not represent a real situation. " << std::endl;
        return;
    }

    std::ofstream dotFile("../../../dots/" + fileName + ".dot");
    if (!dotFile.is_open() || dotFile.fail())
    throw std::runtime_error("Error creating the file!");

    dotFile << "graph G {\n";
    dotFile << "  layout=neato" << ";\n";

    for (std::size_t i = 0; i < this->adjacencyMatrix.size(); ++i) 
    {
        for (std::size_t j = i + 1; j < this->adjacencyMatrix[i].size(); ++j) 
        {
            if (this->adjacencyMatrix[i][j] != 0) 
            {
                double length = std::sqrt(this->adjacencyMatrix[i][j]);
                dotFile << "  " << i << " -- " << j << " [len=" << length << ", style=invis, xlabel=\"" << this->adjacencyMatrix[i][j] << "\"];\n";
            }
        }
    }

    dotFile << "}\n";
    dotFile.close();

    std::string dotFilePath = "../../../dots/" + fileName + ".dot";
    std::string pngFilePath = "../../../maps/" + fileName + ".png";

    std::string command = std::string("neato") + " -Tpng " + dotFilePath + " -o " + pngFilePath;
    system(command.c_str()); 

    std::cout << "A map was successfully generated!" << std::endl;
}

std::vector<std::vector<int>> Engine::generateRandomAdjacencyMatrix(const int &maxDistance, const int &size) 
{
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < size; ++i) 
    {
        for (int j = i + 1; j < size; ++j) 
        {
            int distance = rand() % maxDistance + 1;
            matrix[i][j] = distance;
            matrix[j][i] = distance;
        }
    }

    return matrix;
}

void Engine::Exit()
{
    std::cout << "Exiting program..." << std::endl;
    this->stopProgram = true;
}

void Engine::Close()
{
    this->fileIisOpen = false;
    this->isFileGenerated = false;
    std::cout << "Program successfully closed. The memory is cleared." << std::endl;
}

Engine& Engine::getInstance()
{
    static Engine object;
    return object;
}

void Engine::Exe()
{
    std::cout << "Welcome to the TSP solutions problem!" << std::endl;
    std::cout << "Please, input a command. You can see the available commands with the command \"help\"" << std::endl;
    while (!this->stopProgram)
    {   
        std::string command;
        std::getline(std::cin, command);

        CommandReader cmd(command);
        this->DoCommand(cmd);
    }
}

std::istream& operator>>(std::istream& file, std::vector<std::vector<int>>& other)
{
    other.clear();

    int NumberOfCities;
    file >> NumberOfCities;

    other.resize(NumberOfCities, std::vector<int>(NumberOfCities));

    for (int i = 0; i < NumberOfCities; ++i) 
    {
        for (int j = 0; j < NumberOfCities; ++j) 
        {
            file >> other[i][j];
        }
    }

    return file;
}

bool Engine::fileExists(std::string filename)
{
    std::string CurrentPath;

    char buffer[FILENAME_MAX];
    if (getcwd(buffer, FILENAME_MAX) == nullptr)
    {
        std::cerr << "Error getting current working directory." << std::endl;
        return false;
    }
    CurrentPath = buffer;

    std::string filePath = CurrentPath + "/../../../Examples/" + filename;

    std::ifstream file(filePath);
    bool result = file.good();
    file.close();

    return result;
}

bool Engine::isNewFile(const std::string& filename) 
{
    char buffer[FILENAME_MAX];
    if (_getcwd(buffer, FILENAME_MAX) == nullptr)
    {
        std::cerr << "Error getting current working directory." << std::endl;
        return false;
    }
    std::string CurrentPath = buffer;

    std::string filePath = CurrentPath + "/../../../Examples/" + filename;
    std::ifstream file(filePath);

    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return false;
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.close();

   return (fileSize == 0);
}

bool Engine::isValidFilename(const std::string& filename) 
{
    if (filename.length() < 4)
    return false;

    std::string extension = filename.substr(filename.length() - 4);

    if (extension != ".txt")
    return false;

    return true;
}

void Engine::printMatrix() const
{
    if(this->adjacencyMatrix.size() > 40)
    {
        std::cout << "The graph is too big, sorry" << std::endl;
        return;
    }

    if(this->adjacencyMatrix.size() < 1)
    {
        std::cout << "There is no graph to print out" << std::endl;
        return;
    }

    std::cout << "The adjacency matrix for the graph is: " << std::endl;

    std::cout << "\t";
    for (size_t i = 0; i < this->adjacencyMatrix.size(); ++i) 
    {
        std::cout << i << '\t';
    }
    std::cout << std::endl;

    for (size_t i = 0; i < this->adjacencyMatrix.size(); ++i) 
    {
        std::cout << i << '\t';

        for (size_t j = 0; j < this->adjacencyMatrix[i].size(); ++j) 
        {
            std::cout << this->adjacencyMatrix[i][j] << '\t';
        }

        std::cout << std::endl << std::endl;
    }
}

void Engine::Open(std::string &name)
{
    if(this->fileIisOpen)
    {
        std::cout << "A file is already opened!" << std::endl;
        return;
    }

    if(!isValidFilename(name))
    {
        std::cout << "This filename is invalid!" << std::endl;
        return;
    }

    bool fileExist = fileExists(name);
    if(!fileExist)
    {
        std::cout << "No file with such name exists" << std::endl;
        return;
    }
    else if(isNewFile(name))
    {
        std::cout << "The file is empty" << std::endl;
        return;
    }
    else
    {
        char buffern[FILENAME_MAX];
        if (_getcwd(buffern, FILENAME_MAX) == nullptr) 
        {
            std::cerr << "Error getting current working directory." << std::endl;
            return;
        }
        std::string CurrentPath = buffern;
        std::string filePath = CurrentPath + "/../../../Examples/" + name;

        std::ifstream file(filePath);
        if(!file)
        {
            std::cout << "Error opening file" << std::endl;
            return;
        }

        std::cout << "File successfully opened!" << std::endl;
        this->fileIisOpen = true;

        std::vector<std::vector<int>> buffer;
        file >> buffer;
        
        this->adjacencyMatrix.clear();
        this->adjacencyMatrix.assign(buffer.begin(), buffer.end());

        file.close();
    }
}

bool Engine::isNumber(const std::string& str) 
{
    try 
    {
        std::size_t pos = 0;
        std::stod(str, &pos);
        return pos == str.length();
    } 
    catch (const std::invalid_argument&) {return false;} 
    catch (const std::out_of_range&) {return false;}
}

bool Engine::isCommandValid(CommandReader command)
{
    std::string mainCommand = command[0];
    int size = command.getNumberOfArgs();

    if(mainCommand != "open" && mainCommand != "close" && mainCommand != "help" && mainCommand != "bruteforce" && mainCommand != "heldkarp" 
    && mainCommand != "held-karp" && mainCommand != "twoopt" && mainCommand != "nearestneighbour" && mainCommand != "graph" && 
    mainCommand != "exit" && mainCommand != "showmap" && mainCommand != "generate")
    {
        std::cout << "Invalid main command" << std::endl;
        return false;
    }

    if(mainCommand == "open")
    {
        if(size != 2)
        {
            std::cout << "Invalid number of arguments in command" << std::endl;
            return false;
        }
        if(!isValidFilename(command[1]))
        {
            std::cout << "Invalid file name" << std::endl;
            return false;
        }
    }

    if(mainCommand == "generate")
    {
        if(size != 3)
        {
            std::cout << "Invalid number of arguments in command" << std::endl;
            return false;
        }

        if(!isNumber(command[1]) || !isNumber(command[2]))
        {
            std::cout << "Expected a number. " << std::endl;
            return false;
        }

        if(std::stoi(command[1]) < 1 || std::stoi(command[1]) < 1)
        {
            std::cout << "Not valid numbers. " << std::endl;
            return false;
        }
    }

    if(mainCommand == "close" || mainCommand == "help" || mainCommand == "exit" || mainCommand == "graph" || mainCommand == "bruteforce" || mainCommand == "heldkarp" 
    || mainCommand == "held-karp" || mainCommand == "nearestneighbour" || mainCommand == "showmap")
    {
        if(size != 1)
        {
            std::cout << "Invalid number of arguments in command" << std::endl;
            return false;
        }
    }

    if(mainCommand == "twoopt")
    {
        if(size != 2)
        {
            std::cout << "Invalid number of arguments in command" << std::endl;
            return false;
        }
        if(command[1] != "default" && command[1] != "assisted")
        {
            std::cout << "Invalid method for TwoOpt" << std::endl;
            return false;
        }
    }

    return true;
}

void Engine::printHelp()
{
    std::cout << "The following general commands are supported: " << std::endl;
    std::cout << std::endl;

    std::cout << "Open <filename>                              Opens a file with the given name and saves its graph in the memory." << std::endl;
    std::cout << "Generate <distance cap> <size>               Generates a randomized graph of a given size." << std::endl;
    std::cout << "Close                                        Closes the currently open file and clears the memory." << std::endl;
    std::cout << "Exit                                         Exits the program." << std::endl;
    std::cout << std::endl;

    std::cout << "The following commands for work with the algorithms are supported: " << std::endl;
    std::cout << std::endl;

    std::cout << "Graph                                        Prints the currently loaded graph." << std::endl;
    std::cout << "ShowMap                                      Generates a map of the cities with relative distances in order to visualize." << std::endl;
    std::cout << "BruteForce                                   Generates the Bruteforce solution for the TSP." << std::endl;
    std::cout << "Held-Karp                                    Generates the Held-Karp algorithm solution for the TSP." << std::endl;
    std::cout << "TwoOpt <\"default\">                             Generates the TwoOpt solution for the TSP using a default starting route." << std::endl;
    std::cout << "TwoOpt <\"assisted\">                            Generates the TwoOpt solution for the TSP using an optimised* starting route." << std::endl;
    std::cout << "NearestNeighbour                             Generates the Nearest Neighbour algorithm solution for the TSP." << std::endl;
    std::cout << std::endl;

    std::cout << "A list of important notes to keep in mind while using the program: " << std::endl;
    std::cout << std::endl;

    std::cout << "*NOTE: THE GRAPH COMMAND ONLY SUPPORTS UP TO 20x20 GRAPH IN ORDER TO NOT BE OBSOLETE!" << std::endl;
    std::cout << "*NOTE: 1) THE HELD-KARP AND BRUTEFORCE ALGORITHMS ARE EXACT BUT HEAVY TO WORK WITH WHICH IS WHY THEY DO NOT SUPPORT BIG GRAPHS" << std::endl;
    std::cout << "       2) ONLY THE HELD-KARP AND BRUTEFORCE ALGORITHMS OFFER EXACT SOLUTIONS" << std::endl;
    std::cout << "       3) THE TWOOPT AND NEAREST NEIGHBOUR ALGORITHMS ARE FASTER AND SUPPORT MUCH BIGGER GRAPHS!" << std::endl;
    std::cout << "       4) THE TWOOPT AND NEAREST NEIGHBOUR ALGORITHMS ARE HEURISTICS - THEY ARE NOT EXACT AND OFFER A CLOSE APROXIMATION ONLY!" << std::endl;
    std::cout << "*NOTE: THE TWO OPT ALGORITHM REQUIRES A STARTING ROUTE AND USING A FAST HEURISTIC TO CALCULATE A SEMI OPTIMISED ROUTE CAN HEAVILY" << std::endl;
    std::cout << "REDUCE THE WORKLOAD OF THE ALGORITHM. THE ASSISTED ROUTE GENERATOR USES THE NEAREST NEIGHBOUR ALGORITHM. THE DEFAULT STARTING ROUTE" << std::endl;
    std::cout << "IS A GENERATED ROUTE FROM THE FIRST TO THE LAST CITY." << std::endl;

    std::cout << "*IMPORTANT: THE FORMAT OF THE FILENAMES IS \"NAME.TXT\"" << std::endl;
    std::cout << std::endl;
}

void Engine::generateGraph(const int &maxDistance, const int &size)
{
    this->isFileGenerated = true;
    this->fileIisOpen = true;

    this->adjacencyMatrix = generateRandomAdjacencyMatrix(maxDistance, size);
    std::cout << "An adjacency matrix was successfully generated!" << std::endl;
}

void Engine::DoCommand(CommandReader command)
{
    if (!isCommandValid(command))
    {
        return;
    }

    std::string mainCommand = command[0];
    std::size_t size = command.getNumberOfArgs();
    
    if (mainCommand == "help") 
    {
        this->printHelp();
    }
    else if (mainCommand == "close")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open. You cannot perform the \"close\" action." << std::endl;
        }
        else
        {
            this->currentFileName = "";
            this->Close();
        }
    }
    else if (mainCommand == "exit") 
    {
        this->Exit();
    }
    else if (mainCommand == "open")
    {
        if(this->fileIisOpen)
        {
            std::cout << "A file is currently open. You cannot perform the \"Open\" action again unless you close the current file." << std::endl;
        }
        else
        {
            this->currentFileName = command[1];
            this->Open(command[1]);
        }
    }
    else if (mainCommand == "generate")
    {
        if(this->fileIisOpen)
        {
            std::cout << "A file is currently open. You cannot perform the \"Generate\" action again unless you close the current file." << std::endl;
        }
        else
        {
            this->generateGraph(std::stoi(command[1]), std::stoi(command[2]));
        }
    }
    else if (mainCommand == "graph")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open. There is no graph in the memory." << std::endl;
        }
        else
        this->printMatrix();
    }
    else if (mainCommand == "showmap")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open. There is no graph in the memory to map." << std::endl;
        }
        else
        this->createMap(this->currentFileName.substr(0, this->currentFileName.size() - 4) + "_map");
    }
    else if (mainCommand == "bruteforce")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open. There is no graph to perform the brutoforce solution on." << std::endl;
        }
        else
        this->findSolutionBruteForce(this->currentFileName.substr(0, this->currentFileName.size() - 4) + "BF");
    }
    else if (mainCommand == "heldkarp" || mainCommand == "held-karp")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open. There is no graph to perform the Held-Karp algorithm solution on." << std::endl;
        }
        else
        this->findSolutionHK(this->currentFileName.substr(0, this->currentFileName.size() - 4) + "HK");
    }
    else if (mainCommand == "nearestneighbour")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open. There is no graph to perform the Nearest neighbour algorithm solution on." << std::endl;
        }
        else
        this->findSolutionNearestNeighbour(this->currentFileName.substr(0, this->currentFileName.size() - 4) + "NN");
    }
    else if (mainCommand == "twoopt" && command[1] == "default")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open. There is no graph to perform the TwoOpt algorithm solution on." << std::endl;
        }
        else
        {
            std::vector<int> tour; 
            for (int i = 0; i < this->adjacencyMatrix.size(); ++i) 
            {
                tour.push_back(i);
            }
            tour.push_back(0);
            this->findSolutionTwoOpt(tour, this->currentFileName.substr(0, this->currentFileName.size() - 4) + "TOD");
        }
    }
    else if (mainCommand == "twoopt" && command[1] == "assisted")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open. There is no graph to perform the TwoOpt algorithm solution on." << std::endl;
        }
        else
        {
            NearestNeighbor object(this->adjacencyMatrix);
            object.run();
            this->findSolutionTwoOpt(object.getPath(), (this->currentFileName.substr(0, this->currentFileName.size() - 4) + "TOA"));
        }
    }
}