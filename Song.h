/**
 * Aaron Luciano
 * CS2240
 * Section A
 * 9-20-2023
 * Project 2
 */

#ifndef CS2240_PROJECT_1_SONG_H
#define CS2240_PROJECT_1_SONG_H

#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <cassert>
using namespace std;
using std::string;

// Struct for Project 5
struct SongInfo{
    string track;
    string artist;

    // Default Constructor
    SongInfo() = default;

    // Constructor w/ parameters
    SongInfo(string track, string artist) : track(std::move(track)), artist(std::move(artist)) {}
};

/**
 * Class representing entries from my personal playlists pulled form spotify
 * CSV Files were pulled from my own spotify library. See: https://exportify.net/
 * for how this was done
 *
 * Fields (naming follows abbreviations used in CSV file):
 *     rowid: a unique integer indicating row in source data
 *     track: title of song track from data set
 *     album: title of album from respective song in the data set
 *     artist: name or names of artist(s) who the track was written by
 *     release: string containing the year, month and day the track was release to spotify on
 *     genre: the genre of the music from the respective track
 *        genre is preassigned by spotify upon downloading each song / the playlists csv
 *     duration: total duration of the track in milliseconds
 */
class Song{
private:
    ifstream inFile;
    string header;
    std::string track, album, artist, release, genre;
    int rowid, duration;

public:
    // Constructors
    Song(){
        // sets song with default values
    }

    Song(int rowid,
         string track,
         string album,
         string artist,
         string release,
         string genre,
         int duration){
        this->rowid = rowid;
        this->track = track;
        this->album = album;
        this->artist = artist;
        this->release = release;
        this->genre = genre;
        this->duration = duration;
    }

    // Copy Constructor
    Song(const Song& other){
        this->rowid = other.rowid;
        this->track = other.track;
        this->album = other.album;
        this->artist = other.artist;
        this->release = other.release;
        this->genre = other.genre;
        this->duration = other.duration;
    }

    // Copy Assignment Operator
    Song& operator=(const Song& other){
        if(this == &other){
            return * this;
        }
        // copying variable from 'other' to 'this'
        this->rowid = other.rowid;
        this->track = other.track;
        this->album = other.album;
        this->artist = other.artist;
        this->release = other.release;
        this->genre = other.genre;
        this->duration = other.duration;

        return *this;
    }

    // Getters
    int getRowId() const{
        return rowid;
    }

    string getTrack() const{
        return track;
    }

    string getAlbum() const{
        return album;
    }

    string getArtist() const{
        return artist;
    }
    string getRelease() const{
        return release;
    }

    string getGenre() const{
        return genre;
    }

    int getDuration() const{
        return duration;
    }

    // Setters
    void setRowId(int rowid){
        this->rowid = rowid;
    }

    void setTrack(string track){
        this->track = track;
    }

    void setAlbum(string album){
        this->album = album;
    }

    void setArtist(string artist){
        this->artist = artist;
    }

    void setRelease(string release){
        this->release = release;
    }

    void setGenre(string genre){
        this->genre = genre;
    }

    void setDuration(int duration){
        this->duration = duration;
    }

    // overload method for printing of song objects
    friend std::ostream& operator<<(std::ostream& os, const Song& song){
        os << "Track: " << song.getTrack() << endl;
        os << "Album: " << song.getAlbum() << endl;
        os << "Artist: " << song.getArtist() << endl;
        os << "Release Date: " << song.getRelease() << endl;
        os << "Genre: " << song.getGenre() << endl;
        os << "Duration (ms): " << song.getDuration() << endl;
        os << "---------------";
        return os;
    }

    // Overload methods for insertion (Project 3)
    bool operator<(const Song& other) const{
        return this->rowid < other.rowid;
    }

    bool operator>(const Song& other) const{
        return this->rowid > other.rowid;
    }

    bool operator<=(const Song& other) const{
        return this->rowid <= other.rowid;
    }

    bool operator>=(const Song& other) const{
        return this->rowid >= other.rowid;
    }

    bool operator==(const Song& other) const{
        return this->rowid == other.rowid;
    }


};

/**
 * VERY important method. Many of the titles, artists and most
 * of the genres contain commas. This allows those fields to be
 * read without seeing the commas as delimiters and allows all
 * rows of the csv to parse properly.
 * @params inFile
 */
string parseCSVRow(ifstream& inFile){
    string field;
    char c;

    // Check if the field is enclosed in double quotes
    if (inFile.peek() == '"'){
        inFile.ignore(); // Ignore the opening double quote
        while (inFile.get(c)){
            if (c == '"') {
                if (inFile.peek() == '"'){
                    // Consecutive double quotes within the field
                    field += c; // Add one double quote to the field
                    inFile.ignore(); // Ignore the second double quote
                }
                else{
                    // End of the quoted field
                    break;
                }
            }
            else{
                field += c;
            }
        }
        // Consume the delimiter ( comma) if present
        if (inFile.peek() == ','){
            inFile.ignore();
        }
    }
    else{
        // Field is not enclosed in double quotes
        getline(inFile, field, ',');
    }
    return field;
}

/**
 * Method to get just track and artist for songInfo
 * (Project 5)
 */
void getDataForSongInfo(vector<SongInfo> &songInfos){
    ifstream inFile;
    inFile.open("../songInfo.csv");

    // Read and discard header
    string header;
    getline(inFile, header);

    string track, artist;

    while (inFile && inFile.peek() != EOF) {
        // Track Name
        track = parseCSVRow(inFile);
        // Artist Name
        artist = parseCSVRow(inFile);
        // Consume the newline character if it's not the end of the file
        if (inFile.peek() == '\n'){
            inFile.get();
        }
        // Put data from line into a SongInfo object
        songInfos.push_back(SongInfo(track, artist));
    }
    inFile.close();
}

/**
 * Read data into a vector from the downloaded CSV file
 * @param songs
 */
void getDataFromFile(vector<Song> & songs){
    ifstream inFile;

    inFile.open("../merged-songs.csv");

    // Reads Header but prints nothing (intentionally)
    std::string header = "";
    getline(inFile, header);

    int rowid;
    string track, album, artist, release, genre;
    int duration;

    /*
     * NOTE: all instances of cout are commented out intentionally,
     * removing the // will allow you to see each individual song printed
     * with all of its attributes
     */
    while (inFile && inFile.peek() != EOF){
        // Reading information from CSV dataset

        // Row ID
        inFile >> rowid; // Read the integer value
        //cout << "Row ID: " << rowid << endl;
        char delimiter = ','; // Declare a variable to store the delimiter
        inFile >> delimiter; // Read the delimiter (e.g., comma)

        // Track Name
        track = parseCSVRow(inFile);


        // Album Name
        album = parseCSVRow(inFile);

        // Artist Name
        artist = parseCSVRow(inFile);

        // Release Date
        getline(inFile, release, ',');
        //cout << "Release Date: " << release << endl;

        // Genre
        genre = parseCSVRow(inFile);

        // Duration (ms)
        inFile >> duration;
        //cout << "Duration (ms): " << duration << endl;

        // Consume the newline character
        while (inFile.peek() != '\n' && inFile.peek() != EOF){
            inFile.get(); // Consume and discard characters until newline or EOF
        }

        // Consume the newline character itself
        if (inFile.peek() == '\n'){
            inFile.get();
        }

        // Put data from line into a Song object
        songs.push_back(Song(rowid,track,album,artist,
                                 release,genre,duration));

    }
    inFile.close();
}
/**
 * Reads in all songs and sums them to give
 * their total duration
 *
 * @param songs
 * @return total duration of all songs
 */
int calculateTotalDuration(const vector<Song>& songs){
    int totalDuration = 0;
    for (const Song& song : songs) {
        totalDuration += song.getDuration();
    }
    return totalDuration;
}

/**
 * Calculates the average duration of songs based on
 * total duration previously found in calculateTotalDuration
 * by dividing them by the total size of the vector
 *
 * @param songs
 * @return average duration of all songs
 */
double averageDuration(const vector<Song>& songs){
    int totalDuration = calculateTotalDuration(songs);
    return static_cast<double>(totalDuration) / static_cast<double>(songs.size());
}

/**
 * Gets average release year among all songs by
 * finding the year of release within the first 4 characters
 * of the release string and converting them to an int,
 * then averaging them by the total amount of songs in the vector
 *
 * @param songs
 * @return average year of release for all songs
 */
int getAverageReleaseYears(const vector<Song>& songs){
    int allReleaseYears = 0;
    int averageReleaseYear = 0;
    for (const Song& song: songs){
        string releaseYearStr = song.getRelease().substr(0,4);
        int releaseYear = stoi(releaseYearStr);
        allReleaseYears += releaseYear;
        averageReleaseYear = allReleaseYears / songs.size();
    }
    return averageReleaseYear;
}

// To pull ONLY the years from Release Dates
int getReleaseYear(const string& release){
    return std::stoi(release.substr(0,4));
}

/**
 * Method for testing to make sure
 * all setters and getters work properly
 * for when / if they are needed.
 */

void testSongs(){
    Song testObject;
    // Test setters and getters
    testObject.setRowId(1);
    assert(testObject.getRowId() == 1);

    testObject.setTrack("Track1");
    assert(testObject.getTrack() == "Track1");

    testObject.setAlbum("Album1");
    assert(testObject.getAlbum() == "Album1");

    testObject.setArtist("Artist1");
    assert(testObject.getArtist() == "Artist1");

    testObject.setRelease("2023-09-11");
    assert(testObject.getRelease() == "2023-09-11");

    testObject.setGenre("Genre1");
    assert(testObject.getGenre() == "Genre1");

    testObject.setDuration(300000); // 5 minutes in milliseconds
    assert(testObject.getDuration() == 300000);

    // Test initialization (and getters)
    Song testObject2(2, "Track2", "Album2", "Artist2",
                     "2023-09-12", "Genre2", 240000); // 4 minutes in milliseconds
    assert(testObject2.getRowId() == 2);
    assert(testObject2.getTrack() == "Track2");
    assert(testObject2.getAlbum() == "Album2");
    assert(testObject2.getArtist() == "Artist2");
    assert(testObject2.getRelease() == "2023-09-12");
    assert(testObject2.getGenre() == "Genre2");
    assert(testObject2.getDuration() == 240000);
}


#endif //CS2240_PROJECT_1_SONG_H
