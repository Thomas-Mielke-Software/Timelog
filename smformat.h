class StreamFormat
{
	public:
	StreamFormat::StreamFormat(char *);
	StreamFormat::~StreamFormat();
	char *GetText(long Line, long left_bound, long right_bound); // gibt den Text von Zeile Line ab 
																 // Zeichen left_bound bis Zeichen right_bound zurück
	long ColSum(long left_bound, long right_bound, char *date_from, char *date_to, char kuerzel);	 // gibt die Gesamtsumme aller Zahlen die sich in der angegebenen Spalte befinden zurück
	long GetRows();	 // gibt die Anzahl aller Zahlen an
	int StreamFormat::CompareDates(char * d1, char * d2);

	private:
	struct StreamFormatBuffer 
	{
		char *Line;
		StreamFormatBuffer *next;
	};
	struct StreamFormatBuffer *StreamFormatBufferBase;
};

