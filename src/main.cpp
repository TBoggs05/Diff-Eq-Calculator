#include "eulers.h"
#include "crow.h"
/*//CODE FOR CONSOLE VERSION!
char menu(){
    char x;
    std::cout<<"Select Method to Solve Differential Equation:"<<std::endl;
    std::cout<<"1.)Eulers Method(Numerical Solution/Approximation)"<<std::endl;
    std::cout<<"2.)Taylor's Method(Power Series Solution)"<<std::endl;
    std::cout<<"E.)Exit"<<std::endl;
    std::cin>>x;
    return x;
}
*/
int main(){
    /*class organizes all the different parts of Crow and provides the dev a simple interface to interact w/ these parts.*/
    crow::SimpleApp app; //crow framework::SimpleApp object. 
    CROW_ROUTE(app, "/")([](){
        return crow::mustache::load("index.html").render();
    });

    //define your endpoint at root directory
    CROW_ROUTE(app, "/calculate").methods("POST"_method)([](const crow::request& req){ //POST API Endpoint
        auto args = crow::json::load(req.body);//load data from our request method

        if(!args){
            return crow::response(400, "Invalid JSON format.");
        }
            
        //extract data from our recieved JSON 
        double initial_x = args["initial_x"].d();
        double initial_y = args["initial_y"].d();
        double step_size = args["step_size"].d();
        double end_x = args["end_x"].d();
        std::string equation = args["equation"].s();
        eulers approximator;
        double result = 0;
        std::vector<std::string> steps;
        if(approximator.start(equation, initial_x, step_size, end_x, initial_y)){
            result=approximator.eulers_calculate(approximator.equation);
            std::cout<<result<<std::endl;
            steps = approximator.getSteps();//grabs the vector of strings.
        }
        else{
            //return the error as JSON
            crow::json::wvalue err;
            err["error"] = approximator.getErrString();
            
            crow::response res;
            res.code = 400; //error code.
            res.set_header("Conent-Type", "application/json"); // set our header data
            res.body = err.dump(); //convert JSON object to string

            return res;
        }

        //return the result as JSON
        crow::json::wvalue res;
        res["result"] = result;
        res["steps"] = steps; //send our step vector
        return crow::response(res);
    });

    app.port(18080).multithreaded().run();//.port()->defines port(if not used, will use port 80)
                                            //multithreaded()->I assume it allows for multiple client requests at once!
                                            //run()->run the application

/*  CONSOLE APP CODE
    char input[2];
    while(std::tolower(input[0]) !='e'){
        input[0] = menu();
        switch(input[0]){
            case '1':{
            eulers approximator;
            approximator.start();
            break;
            }
                case '2':{
                cout<<"SERIES Calculator!\n"<<endl;
                cout<<"Will be implemented at a future date...\n"<<endl;
                break;
                }
                    case 'E':
                    case 'e':
                    cout<<"Exiting...\n"<<endl;
                    break;
                        default:
                        cout<<"invalid input.\n"<<endl;
                        break;
        }
    }
    */
return 0;
}