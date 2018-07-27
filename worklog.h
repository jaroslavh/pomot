#include <string>

using namespace std;

class Worklog
{
    public:
        //Opens worklog by creating a new file in worklog directory, name yy-mm-dd-hh-worklog.txt
        Worklog();
        //open()
        int worklog_open();
        //close() TODO

        //appends string to the file
        int worklog_append(const string &line);
        //open
        bool exists(const string &name);

        //Returns filename as a string
        string get_filename() { return filename; }
        //Returns directory where we save this log as a string
        string get_directory() { return directory; } //TODO maybe git whole pwd

    private:
        string filename;
        string directory;
        ofstream file;
};
