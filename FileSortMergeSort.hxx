#pragma once

#include <atomic>
#include <string>

/**
 * file sorting class
 */ 
class FileSortMergeSort 
{

public:

    /** 
     * Constructor
     * @param - number of lines per temp. file
     * @param - file path name
     */
    FileSortMergeSort(size_t uNumberOfLines, const std::string& sFilePathName):
                        m_uNumberOfLines(uNumberOfLines),
                        m_sFilePathName(sFilePathName)
    {
        m_uMergedFileIndex = 0;
    };


    /** 
     * Destructor
     */
    ~FileSortMergeSort() = default;


    /**
     * @brief start the file sorting
     */
    void Start();


    /**
     * @return a reference of the read-only member variable m_sFilePathName
     */
    const std::string& GetFilePathName() const { return m_sFilePathName; };

private:

    static std::string TEMP_FILE_NAME;

    /** 
     * Empty Constructor
     */
    FileSortMergeSort() = delete;


    /**
     * @brief sort the content of input file
     * 
     * @parm sFilePathName - file path and name to load and sort
     * 
     * @return bool if operation is ok
     */
    bool SortFileContent(const std::string& sFilePathName);


    /**
     * @brief merge the content of the two input files
     * 
     * @parm sFileOnePathName - file path and name of first input file
     * @parm sFileTwoPathName - file path and name of second input file
     * 
     * @return file path and name of merged file.
     * @return empty if operation failed
     */
    std::string MergeFileContent(const std::string& sFileOnePathName, const std::string& sFileTwoPathName);


    /**
     * @brief number of lines per temp. file
     */
    size_t              m_uNumberOfLines;

    /**
     * @brief input file path name
     */
    std::string         m_sFilePathName;

    /**
     * @brief merged file index
     */
    std::atomic_size_t  m_uMergedFileIndex;

};


