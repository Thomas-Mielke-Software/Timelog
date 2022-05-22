class StreamFormat
{
	public:
	StreamFormat::StreamFormat(char *);
	StreamFormat::~StreamFormat();
	char *GetText(long Line, long left_bound, long right_bound); // gibt den Text von Zeile Line ab 
																 // Zeichen left_bound bis Zeichen right_bound zur�ck
	long ColSum(long left_bound, long right_bound);	 // gibt die Gesamtsumme aller Zahlen die sich in der angegebenen Spalte befinden zur�ck

	private:
	struct StreamFormatBuffer 
	{
		char *Line;
		StreamFormatBuffer *next;
	};
	struct StreamFormatBuffer *StreamFormatBufferBase;
};

