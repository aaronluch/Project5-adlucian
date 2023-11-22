#include "OpenAddressing.h"
#include "SeparateChaining.h"
#include "Song.h"
#include <vector>
#include <fstream>
using namespace std;

// Method to write read counts to a file
void writeReadCountsToFile(const vector<unsigned long>& readCounts, const string& filename) {
    ofstream outFile(filename);
    outFile << "Size,Reads" << endl;
    int size = 0;
    for (const auto& count : readCounts) {
        outFile << size + 1 << "," << count << endl;
        size ++;
    }
    outFile.close();
}

// Global getKey Functions
string getTrackKey(SongInfo songInfo){
    return songInfo.track;
}
string getTrackArtistKey(SongInfo songInfo){
    return songInfo.track + "_" + songInfo.artist; // Concatenating title and artist
}

int main() {
    vector<SongInfo> songsInfo;
    getDataForSongInfo(songsInfo);
    int sizes[5] = {1031, 1040, 2061, 2080, 2100}; // Sizes for hash tables

    // Creating all hash tables
    vector<SeparateChaining<SongInfo>> scTablesFirstKey;
    vector<SeparateChaining<SongInfo>> scTablesSecondKey;
    for (int i = 0; i < 5; ++i) {
        scTablesFirstKey.push_back(SeparateChaining<SongInfo>(sizes[i], getTrackKey));
        scTablesSecondKey.push_back(SeparateChaining<SongInfo>(sizes[i], getTrackArtistKey));
    }
    vector<QuadraticProbing<SongInfo>> qpTablesFirstKey;
    vector<QuadraticProbing<SongInfo>> qpTablesSecondKey;
    for (int i = 0; i < 5; ++i){
        qpTablesFirstKey.push_back(QuadraticProbing<SongInfo>(sizes[i], getTrackKey));
        qpTablesSecondKey.push_back(QuadraticProbing<SongInfo>(sizes[i], getTrackArtistKey));
    }

    // Insert all SongInfo objects into each of the hash tables
    for (const SongInfo& songInfo : songsInfo){
        for(auto& table : scTablesFirstKey){
            table.insert(songInfo);
        }
        for (auto& table : scTablesSecondKey){
            table.insert(songInfo);
        }
        for (auto& table : qpTablesFirstKey){
            table.insert(songInfo);
        }
        for (auto& table : qpTablesSecondKey){
            table.insert(songInfo);
        }
    }

    // For Separate-Chaining First Key
    vector<unsigned long> scFirstKeyReadCounts;
    for (auto& table : scTablesFirstKey){
        scFirstKeyReadCounts.clear();
        for (const auto& songInfo : songsInfo){
            table.resetReadCount();
            table.insert(songInfo);
            scFirstKeyReadCounts.push_back(table.getReadCount()); // Record read counts
        }
        writeReadCountsToFile(scFirstKeyReadCounts,"../output-data/scTablesFirstKeyReads.csv"); // Write to file
    }
    // For Separate-Chaining Second Key
    vector<unsigned long> scSecondKeyReadCounts;
    for (auto& table : scTablesSecondKey){
        scSecondKeyReadCounts.clear();
        for (const auto& songInfo : songsInfo){
            table.resetReadCount();
            table.insert(songInfo);
            scSecondKeyReadCounts.push_back(table.getReadCount()); // Record read counts
        }
        writeReadCountsToFile(scSecondKeyReadCounts,"../output-data/scTablesSecondKeyReads.csv"); // Write to file
    }

    // For Quadratic Probing First Key
    int tableIndexFirstKey = 1;
    vector<unsigned long> qpFirstKeyReadCounts;
    for (auto& table : qpTablesFirstKey){
        qpFirstKeyReadCounts.clear();
        for (const auto& songInfo : songsInfo){
            table.resetReadCount();
            table.insert(songInfo);
            qpFirstKeyReadCounts.push_back(table.getReadCount()); // Record read counts
        }
        writeReadCountsToFile(qpFirstKeyReadCounts,"../output-data/qpTablesFirstKeyReads.csv"); // Write to file
        cout << "Final size of Quadratic Probing First Key Table " << tableIndexFirstKey << ": " << table.getTableSize() << endl;
        tableIndexFirstKey ++;
    }

    // For Quadratic Probing Second Key
    int tableIndexSecondKey = 1;
    vector<unsigned long> qpSecondKeyReadCounts;
    for (auto& table : qpTablesSecondKey){
        qpSecondKeyReadCounts.clear();
        for (const auto& songInfo : songsInfo){
            table.resetReadCount();
            table.insert(songInfo);
            qpSecondKeyReadCounts.push_back(table.getReadCount()); // Record read counts
        }
        writeReadCountsToFile(qpSecondKeyReadCounts,"../output-data/qpTablesSecondKeyReads.csv"); // Write to file
        cout << "Final size of Quadratic Probing First Key Table " << tableIndexSecondKey << ": " << table.getTableSize() << endl;
        tableIndexSecondKey ++;
    }

    return 0;
}
