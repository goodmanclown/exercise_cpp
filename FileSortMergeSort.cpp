#include "FileSortMergeSort.hxx"

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

string FileSortMergeSort::TEMP_FILE_NAME = "/tmp/filesortms_";

void 
FileSortMergeSort::Start()
{
    if (m_uNumberOfLines == 0 || m_sFilePathName.empty())
    {
        return;
    }

    // open the file
    ifstream fInputFile(m_sFilePathName);

    if (!fInputFile.is_open())
    {
        cerr << "cannot open input file: " << m_sFilePathName << endl;
        return;
    }

    size_t uCountLinesRead = 0;
    size_t uNumberOfTempFiles = 0;
    vector<string> vTempFilesOpened;

    ofstream fOutputFile;

    // complexity is O(N)
    while (!fInputFile.eof())
    {
        string sSentence;
        getline(fInputFile, sSentence);
        std::cout << sSentence << endl;

        if (!sSentence.empty())
        {
            if (uCountLinesRead == 0)
            {   // open a new file
                stringstream sFilePathName;
                
                sFilePathName << TEMP_FILE_NAME;
                sFilePathName << ++uNumberOfTempFiles;

                // create a temp file
                fOutputFile.open(sFilePathName.str());
                if (!fOutputFile.is_open())
                {
                    cerr << "cannot open output file: " << sFilePathName.str() << endl;
                    break;
                }

                // remember the temp file path name
                vTempFilesOpened.push_back(sFilePathName.str());
            }

            // write the sentence to the temp. file
            fOutputFile << sSentence << endl;

            ++uCountLinesRead;

            if (uCountLinesRead >= m_uNumberOfLines)
            {   // reset the count to open a new temp file
                uCountLinesRead = 0;

                // close the output temp. file
                fOutputFile.flush();
                fOutputFile.close();
            }
        } 
    }

    if (uCountLinesRead > 0)
    {
        // close the output temp. file
        fOutputFile.flush();
        fOutputFile.close();
    }

    if (vTempFilesOpened.empty())
    {
        cerr << "input file not sorted" << endl;
        return;
    }

    vector<string> vMergedFiles;

    // sort each temp. file on its own
    for (const auto& entry : vTempFilesOpened)
    {
        // complexity is O(Nlog(N))
        if (SortFileContent(entry))
        {
            vMergedFiles.push_back(entry);
        }
    }

    do
    {
        if ((vMergedFiles.size() % 2) != 0)
        {   // make it even
            vMergedFiles.push_back("");
        }

        vector<string> vMergedFilesTemp;
        for (size_t index=0; index < vMergedFiles.size()-1; index=index+2)
        {   
            // complexity is O(Nlog(N))
            auto sMergeFilePathName = MergeFileContent(vMergedFiles[index], vMergedFiles[index+1]);
            if (!sMergeFilePathName.empty())
            {   // save the file name
                vMergedFilesTemp.push_back(sMergeFilePathName);
            }
        }

        if (vMergedFilesTemp.empty())
        {
            cerr << "input file not sorted" << endl;
            break;
        }

        // replace the content
        vMergedFiles = vMergedFilesTemp;

    } while (vMergedFiles.size() > 1);

    std::cout << endl << "sorted file is " << vMergedFiles[0].c_str() << endl;
}

bool
FileSortMergeSort::SortFileContent(const string& sFilePathName)
{
    if (sFilePathName.empty())
    {   // no file
        return false;
    }

    // open the file
    ifstream fInputFile(sFilePathName);
    if (!fInputFile.is_open())
    {
        cerr << "cannot open temp. file: " << sFilePathName << endl;
        return false;
    }

    // load the file content
    multiset<string> cFileContent;

    // complexity is O(N)
    while (!fInputFile.eof())
    {
        string sRecord;
        getline(fInputFile, sRecord);
        
        if (!sRecord.empty())
        {
            // insert the input to this set
            // complexity is O(Nlog(N))
            cFileContent.insert(sRecord);
        }
    }

    // close the file
    fInputFile.close();

    // write this set back to the temp. file
    // open the file and discard old content
    ofstream fOutputFile(sFilePathName, ofstream::out | ofstream::trunc);
    if (!fOutputFile.is_open())
    {
        cerr << "cannot open temp. file: " << sFilePathName << endl;
        return false;
    }

    // complexity is O(N)
    for (const auto& entry : cFileContent)
    {
        fOutputFile << entry << endl;
    }

    fOutputFile.flush();
    fOutputFile.close();

    return true;
}

string
FileSortMergeSort::MergeFileContent(const string& sFileOnePathName, const string& sFileTwoPathName)
{
    // merge 2 files 
    std::cout << "merge " << sFileOnePathName << " & " << sFileTwoPathName << endl;

    if (sFileOnePathName.empty())
    {   // no file one
        return sFileTwoPathName;
    }

    if (sFileTwoPathName.empty())
    {   // no file two
        return sFileOnePathName;
    }

    // open the files
    ifstream fInputFileOne(sFileOnePathName);
    if (!fInputFileOne.is_open())
    {
        cerr << "cannot open temp. file: " << sFileOnePathName << endl;
        return sFileTwoPathName;
    }

    ifstream fInputFileTwo(sFileTwoPathName);
    if (!fInputFileTwo.is_open())
    {
        cerr << "cannot open temp. file: " << sFileTwoPathName << endl;
        return sFileOnePathName;
    }

    // open the output file
    stringstream ssFileMergePathName;
    ssFileMergePathName << TEMP_FILE_NAME;
    ssFileMergePathName << "merged_";
    ssFileMergePathName << ++m_uMergedFileIndex;

    auto sFileMergePathName = ssFileMergePathName.str();

    ofstream fOutputFile(sFileMergePathName, ofstream::out | ofstream::trunc);
    if (!fOutputFile.is_open())
    {
        cerr << "cannot open temp. file: " << sFileMergePathName << endl;
        return "";
    }

    // complexity is O(N)
    string sSentenceOne;
    string sSentenceTwo;
    while (!fInputFileOne.eof() && !fInputFileTwo.eof())
    {
        // get a sentence from each file
        if (sSentenceOne.empty())
        {
            getline(fInputFileOne, sSentenceOne);
        }
        
        if (sSentenceTwo.empty())
        {
            getline(fInputFileTwo, sSentenceTwo);
        }

        if (!sSentenceOne.empty() && !sSentenceTwo.empty())
        {
            if (sSentenceOne > sSentenceTwo)
            {
                fOutputFile << sSentenceTwo << endl;
                sSentenceTwo.clear();
            }
            else if (sSentenceOne < sSentenceTwo)
            {
                fOutputFile << sSentenceOne << endl;    
                sSentenceOne.clear();
            }
            else
            {   // write both if they are equal
                fOutputFile << sSentenceOne << endl;    
                fOutputFile << sSentenceTwo << endl;    
                sSentenceOne.clear();
                sSentenceTwo.clear();
            }
        }
        else if (sSentenceOne.empty())
        {
            fOutputFile << sSentenceTwo << endl;
            sSentenceTwo.clear();
        }
        else
        {
            fOutputFile << sSentenceOne << endl;    
            sSentenceOne.clear();
        }
    }

    if (fInputFileOne.eof() && !fInputFileTwo.eof())
    {   // write the remains of file two
        while (!fInputFileTwo.eof())
        {
            getline(fInputFileTwo, sSentenceTwo);
            if (!sSentenceTwo.empty())
            {
                fOutputFile << sSentenceTwo << endl;
            }
        }
    }
    else if (!fInputFileOne.eof() && fInputFileTwo.eof())
    {   // write the remains of file one
        while (!fInputFileOne.eof())
        {
            getline(fInputFileOne, sSentenceOne);
            if (!sSentenceOne.empty())
            {
                fOutputFile << sSentenceOne << endl;
            }
        }
    }

    // close the file
    fInputFileOne.close();
    fInputFileTwo.close();

    fOutputFile.flush();
    fOutputFile.close();

    std::cout << "merge " << sFileOnePathName << " & " << sFileTwoPathName << " into " << sFileMergePathName << endl;

    return sFileMergePathName;
}
