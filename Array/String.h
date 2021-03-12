#pragma once

class String {
    public:
        String(char * init);
        int Length();
        int FastFind(String pat);
        void FailureFunction();
        String Concat(String t);
        String Substr(int i, int j);
    private:
        char * str;
        int * f;
};