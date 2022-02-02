# include "Board.h"

Board::Board(){
    this->pieces = map<color, vector<Box> >{
        {color::green, {{0, box_type::home, color::green},{0, box_type::home, color::green},{0, box_type::home, color::green},{0, box_type::home, color::green}}},
        {color::red, {{0, box_type::home, color::red},{0, box_type::home, color::red},{0, box_type::home, color::red},{0, box_type::home, color::red}}},
        {color::blue, {{0, box_type::home, color::blue},{0, box_type::home, color::blue},{0, box_type::home, color::blue},{0, box_type::home, color::blue}}},
        {color::yellow, {{0, box_type::home, color::yellow},{0, box_type::home, color::yellow},{0, box_type::home, color::yellow},{0, box_type::home, color::yellow}}}
    };
}
    

Board::Board (const map <color, vector <Box> > & b){
    this->pieces = map<color, vector<Box> >(b);
}


const Box & Board::getPiece(const color c, const int idx) const{
    return pieces.at(c)[idx];
}

const vector<Box> & Board::getPieces(const color c) const{
    return pieces.at(c);
}

void Board::movePiece(const color c, const int idx, const Box & final_box){
    pieces[c][idx] = final_box;
}

