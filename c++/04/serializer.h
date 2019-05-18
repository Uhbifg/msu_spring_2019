#pragma once
#include <iostream>
#include <sstream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    std::ostream &out_;
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
            : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT &&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }

private:
    Error process(bool &val){
        out_ << (val ? "true" : "false") << Separator;
        return out_ ? Error::NoError : Error::CorruptedArchive;
    }
    Error process(uint64_t& val){
        out_ << val << Separator;
        return out_ ? Error::NoError : Error::CorruptedArchive;
    }
    template <class valT, class... ArgsT>
    Error process(valT&& val, ArgsT&&... args){
        Error status = process(std::forward<valT>(val));
        if(status == Error::CorruptedArchive){
            return Error::CorruptedArchive;
        }
        return process(std::forward<ArgsT>(args)...);
    }
};


class Deserializer{
    std::istream& in_;
public:

    Deserializer(std::istream& in):
            in_(in)
    {
    }

    template <class T>
    Error load(T& object){
        return object.serialize(*this);
    }

    template <class ... ArgsT>
    Error operator()(ArgsT&& ... args){
        return process(std::forward<ArgsT>(args)...);
    }

private:
    Error process(bool &val){
        std::string text;
        in_ >> text;

        if (text == "true"){
            val = true;
        }else if (text == "false"){
            val = false;
        }else{
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error process(uint64_t& val){
        std::string text;
        uint64_t temp;
        in_ >> text;
        for(auto digit : text){
            if(!isdigit(digit)){
                return Error::CorruptedArchive;
            }
        }
        std::stringstream number(text);
        number >> temp;
        if(!number){
            return Error::CorruptedArchive;
        }
        val = temp;
        return Error::NoError;
    }

    template <class valT, class... ArgsT>
    Error process(valT&& val, ArgsT&&... args){
        Error status = process(std::forward<valT>(val));
        if(status == Error::CorruptedArchive){
            return Error::CorruptedArchive;
        }
        return process(std::forward<ArgsT>(args)...);
    }
};