///////////////////////////////////
/// \includes
////////////////////////////////////
#include "messageparser.h"
///////////////////////////////////
/// \brief namespace
////////////////////////////////////
namespace messageParser
{
    ///////////////////////////////////
    /// \brief      Message parser class
    ////////////////////////////////////
    MessageParser::MessageParser()
    {
    }
    ///////////////////////////////////
    /// \brief      Destructor message parser class
    ////////////////////////////////////
    MessageParser::~MessageParser()
    {
    }
    ///////////////////////////////////
    /// \brief      Convert Hexadecimal to ASCII
    /// \param[in]  in_pipeline_data
    ////////////////////////////////////
    void MessageParser::hexaToASCII(PipelineData &in_pipeline_data)
    {
        std::string newString;
        for(int i=0; i< in_pipeline_data.body.length(); i+=2)
        {
            std::string byte = in_pipeline_data.body.substr(i,2);
            char chr = (char) (int)strtol(byte.c_str(), NULL, 16);
            newString.push_back(chr);
        }
        in_pipeline_data.body.clear();
        in_pipeline_data.body = newString;
    }
    ///////////////////////////////////
    /// \brief Print pipelines id as group
    ////////////////////////////////////
    void MessageParser::printId(const PipelineData &in_pipeline_data) const
    {
        std::cout << s_PIPELINE << in_pipeline_data.pipeline_id << std::endl;
    }
    ///////////////////////////////////
    /// \brief Print grouped pipelines id's datas
    ////////////////////////////////////
    void MessageParser::print(const PipelineData &in_pipeline_data) const
    {
        std::cout << std::setw(4) << in_pipeline_data.id << s_PIPE_STR_KEY << in_pipeline_data.body;
    }
    ///////////////////////////////////
    /// \brief Sort the pipelines id's and also id's with O(N log N)
    /// \param[in] in_pipeline_data ... pipeline data
    ////////////////////////////////////
    void MessageParser::sortByID(std::vector<PipelineData> &in_pipeline_data)
    {
        std::sort(in_pipeline_data.begin(), in_pipeline_data.end(), [](PipelineData a, PipelineData b){
            if (a.pipeline_id != b.pipeline_id)
                return a.pipeline_id < b.pipeline_id; // Sort pipeline_ids
            else
                return a.id < b.id; // Sort within the pipeline_ids by PipelineData ids
        });

    }
    ///////////////////////////////////
    /// \brief main function to make parser
    ////////////////////////////////////
    void MessageParser::parser(const std::string& in_message_path)
    {
        std::ifstream m_file (in_message_path); // Add text file with all path
        if(!m_file.is_open())
        {
            std::cerr << "Could not open the file - '"
                      << in_message_path << "'" << std::endl;
            return;
        }
        while (std::getline(m_file, m_text_line) )
        {
            std::istringstream iss(m_text_line); // Create a string stream from the line

            ///< To counter for how many lines couldn't read because of broken data
            if(m_text_line.find(S_ERROR_STR0) != std::string::npos)
            {
                ++m_error_count;
                continue;
            }
            if(m_text_line.find(S_ERROR_STR1) != std::string::npos)
            {
                ++m_error_count;
                continue;
            }
            if(m_text_line.find(s_ERROR_STR2) != std::string::npos)
            {
                ++m_error_count;
                continue;
            }

            PipelineData data; ///< To store data in custom struct
            if (!(iss >> data.pipeline_id >> data.id >> data.encoding >> data.body >> data.next_id))
                continue; // Skip the line if parsing fails

            if(data.next_id == -1)
            {
                auto result =  std::find(m_finished_piplines.begin(),m_finished_piplines.end(), data.pipeline_id);
                if(result != std::end(m_finished_piplines))
                     continue;
                else m_pipeline_data.push_back(data); // Store the struct in the container
                m_finished_piplines.push_back(data.pipeline_id);
            }else
            {
                auto result =  std::find(m_finished_piplines.begin(),m_finished_piplines.end(), data.pipeline_id);
                if(result != std::end(m_finished_piplines))
                     continue;
                else
                    m_pipeline_data.push_back(data); // Store the struct in the container
            }

        }
        std::cout << std::endl;

        std::cerr << "Error count " << m_error_count << std::endl << std::endl; // Print how many error faced
        sortByID(m_pipeline_data);   // Sort parsed txt file

        int current_pipelineIds= -1;
        for (auto& data : m_pipeline_data)
        {
            if (data.pipeline_id != current_pipelineIds)
            {
                current_pipelineIds = data.pipeline_id;
                printId(data);
            }
            if(data.encoding == true)
                hexaToASCII(data);
            print(data);
            std::cout << std::endl;
        }
    }

};///< eof
