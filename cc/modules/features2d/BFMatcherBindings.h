#include "BFMatcher.h"
#include "DescriptorMatch.h"

#ifndef __FF_BFMATCHERBINDINGS_H_
#define __FF_BFMATCHERBINDINGS_H_

namespace BFMatcherBindings {

struct MatchWorker : public CatchCvExceptionWorker {
    public:
        cv::BFMatcher bfmatcher;

        MatchWorker(cv::BFMatcher _bfmatcher) {
            this->bfmatcher = _bfmatcher;
        }

        cv::Mat descFrom;
        cv::Mat descTo;
        std::vector<cv::DMatch> dmatches;

        std::string executeCatchCvExceptionWorker() {
            bfmatcher.match(descFrom, descTo, dmatches);
            return "";
        }

        bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
            return Mat::Converter::arg(0, &descFrom, info)
                || Mat::Converter::arg(1, &descTo, info);
        }

        FF_VAL getReturnValue() {
            return ObjectArrayConverter<DescriptorMatch, cv::DMatch>::wrap(dmatches);
        }
    };
}

#endif
