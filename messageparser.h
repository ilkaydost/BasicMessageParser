#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H
///////////////////////////////////
/// \includes
////////////////////////////////////
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <map>
///////////////////////////////////
/// \namespace
////////////////////////////////////
namespace messageParser
{
    static const std::string S_ERROR_STR0 = "   ";
    static const std::string S_ERROR_STR1 = "err";
    static const std::string s_ERROR_STR2 = "...";
    static const std::string s_PIPELINE = "Pipeline ";
    static const std::string s_PIPE_STR_KEY = "|";
    ///////////////////////////////////
    /// \brief The PipelineData class
    ////////////////////////////////////
    struct PipelineData {
        int16_t pipeline_id;
        int id;
        bool encoding;
        std::string body;
        int next_id;
    };

    ///////////////////////////////////
    /// \brief Message parser class
    ////////////////////////////////////
    class MessageParser
    {
        public:
            explicit                    MessageParser   ();
                                        ~MessageParser  ();
            void                        hexaToASCII     (PipelineData& in_pipeline_data);
            void                        printId         (const PipelineData& in_pipeline_data) const;
            void                        print           (const PipelineData& in_pipeline_data) const;
            void                        sortByID        (std::vector<PipelineData>& in_pipeline_data);
            void                        parser          (const std::string& in_message_path);

            ///< Getters
            std::vector<PipelineData>   pipelineData    () const {return m_pipeline_data;};
            std::string                 textLine        () const {return m_text_line; };
            int                         errorCount      () const {return m_error_count; };
            std::vector<int>            finishedPipeline() const {return m_finished_piplines; };

            ///< Setters
            void                        setpipelineData (std::vector<PipelineData> in_pipeline_data)
                                                        {m_pipeline_data = in_pipeline_data; }

            void                        setTextLine     (std::string in_text_line)
                                                        {m_text_line = in_text_line; }

            void                        setErrorCount   (int in_error_count)
                                                        {m_error_count = in_error_count; }

            void                        setFinishedPipeline(std::vector<int> in_finished_pipelines)
                                                        {m_finished_piplines = in_finished_pipelines;}

        private:
            int                         m_error_count       = 0; ///< When dont face it proper line
            std::vector<PipelineData>   m_pipeline_data     = {};
            std::ifstream               m_file              = {};
            std::string                 m_text_line         = {};
            std::vector<int>            m_finished_piplines = {};

    };
}// namespace
#endif // MESSAGEPARSER_H
