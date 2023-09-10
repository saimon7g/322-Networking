#include <bits/stdc++.h>
// #include <windows.h>
using namespace std;

/*











my machine is linux.                   ***        Windows.h was not supported in my machine.            ***






 so, i used the following code to change the color of the text in the terminal


cout << "\033[32m" << "green text" << "\033[0m" << endl;
cout << "\033[31m" << "red text" << "\033[0m" << endl;
cout << "\033[36m" << "cyan text" << "\033[0m" << endl;













*/

void AddPadding(string &s, int m)
{
    int len = s.length();
    int rem = len % m;
    if (rem == 0)
    {
        // cout << "No padding required" << endl;
        return;
    }
    int pad = m - rem;
    // cout << "Padding required: " << pad << endl;
    for (int i = 0; i < pad; i++)
    {
        s += '~';
    }
    // cout << "Padded data string: " << s << endl;
    return;
}

int calculateCheckBits(int m)
{
    int r = 0;
    while (pow(2, r) < m + r + 1)
    {
        r++;
    }
    // cout << "Number of check bits required: " << r << endl;
    return r;
}

void printMatrix(bool **matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}
void printCheckbitMatrix(bool **matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        int k = 0;
        for (int j = 0; j < col; j++)
        {
            if (j == pow(2, k) - 1)
            {
                cout << "\033[32m" << matrix[i][j] << "\033[0m";
                k++;
            }
            else
            {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
}
void columnwiseSerialize(bool **matrix, bool *streamToSend, int row, int col)
{
    int k = 0;
    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            streamToSend[k++] = matrix[i][j];
        }
    }
    cout << "data bits after column-wise serialization:" << endl;
    for (int i = 0; i < col * row; i++)
    {
        cout << streamToSend[i];
    }
    cout << endl;
    return;
}
bool *addCRCChecksum(bool *streamToSend, int len, int *crc, int crcLen)
{
    bool *temp = new bool[len + crcLen];
    for (int i = 0; i < len; i++)
    {
        temp[i] = streamToSend[i];
    }
    for (int i = len; i < len + crcLen; i++)
    {
        temp[i] = 0;
    }
    for (int i = 0; i < len; i++)
    {
        if (temp[i] == 1)
        {
            for (int j = 0; j < crcLen + 1; j++)
            {
                temp[i + j] = temp[i + j] ^ crc[j];
            }
        }
    }
    // streamToSend=new bool[len+crcLen];
    // for(int i=0;i<len;i++)
    // {
    //     streamToSend[i]=temp1[i];
    // }
    for (int i = 0; i < len; i++)
    {
        temp[i] = streamToSend[i];
    }
    cout << "data bits after appending CRC checksum <sent frame>:" << endl;
    for (int i = 0; i < len; i++)
    {
        cout << temp[i];
    }
    for (int i = len; i < len + crcLen; i++)
    {
        cout << "\033[36m" << temp[i] << "\033[0m";
    }
    cout << endl;
    return temp;
}
int *addError(bool *streamToSend, int len, double p, int *numError)
{
    int numOfErrors = 0;
    vector<int> v;
    srand(time(0));
    for (int i = 0; i < len; i++)
    {
        double x = 1.00 * rand() / RAND_MAX;
        if (x < p)
        {
            v.push_back(i);
            numOfErrors++;
            streamToSend[i] = streamToSend[i] ^ 1;
        }
    }
    sort(v.begin(), v.end());
    int *errorPos = new int[v.size()];
    for (int i = 0; i < v.size(); i++)
    {
        errorPos[i] = v[i];
    }
    cout << "Received frame:" << endl;
    int k = 0;
    int l = errorPos[k];
    if (v.size() == 0)
    {
        l = -1;
    }
    for (int i = 0; i < len; i++)
    {
        if (i == l)
        {
            cout << "\033[31m" << streamToSend[i] << "\033[0m";
            k++;
            l = errorPos[k];
        }
        else
        {
            cout << streamToSend[i];
        }
    }
    cout << endl;
    *numError = numOfErrors;
    return errorPos;
}

int *calculateCRC(int CRC, int *crcLen)
{
    int x = CRC;
    *crcLen = 0;
    while (x)
    {
        *crcLen = *crcLen + 1;
        x /= 10;
    }
    int *crc = new int[*crcLen];
    x = CRC;
    for (int i = *crcLen - 1; i >= 0; i--)
    {
        crc[i] = x % 10;
        x /= 10;
    }
    *crcLen = *crcLen - 1;
    return crc;
}
void errorDetection(bool *streamToSend, int len, int *crc, int crcLen)
{
    // for(int i=0;i<len;i++)
    // {
    //     cout<<streamToSend[i];
    // }
    // cout<<endl;
    // for(int i=0;i<crcLen+1;i++)
    // {
    //     cout<<crc[i];
    // }

    bool *temp = new bool[len];
    for (int i = 0; i < len; i++)
    {
        temp[i] = streamToSend[i];
    }
    for (int i = 0; i <= len - crcLen; i++)
    {
        if (temp[i] == 1)
        {
            for (int j = 0; j < crcLen + 1; j++)
            {
                temp[i + j] = temp[i + j] ^ crc[j];
            }
        }
    }
    // cout<<"lemgth of temp:"<<len<<endl<<"       crcLen: "<<crcLen<<endl;
    bool flag = true;
    for (int i = len - crcLen; i < len; i++)
    {
        // cout<<i<<"      " << "\033[36m" << temp[i] << "\033[0m";
        if (temp[i])
        {
            flag = false;
            break;
        }
    }
    cout << endl;
    if (flag)
    {
        cout << "Result of CRC checksum matching :No error detected" << endl<<endl;
    }
    else
    {
        cout << "Result of CRC checksum matching :Error detected" << endl << endl;
    }
}

bool* removeChecksumBits(bool *streamToSend, int len, int crcLen)
{
    bool *temp = new bool[len - crcLen];
    for (int i = 0; i < len - crcLen; i++)
    {
        temp[i] = streamToSend[i];
    }
    // cout << "data bits after removing CRC checksum:" << endl;
    // for (int i = 0; i < len - crcLen; i++)
    // {
    //     cout << temp[i];
    // }
    // cout << endl<<endl;
    return temp;
}

int *deserialiseColumnwise(bool **receivedMatrix, bool *streamToSend, int *errorPosition, int row, int col, int len, int numOfErrors)
{
    int k = 0;
    int l = errorPosition[k];
    int m = 0;
    vector<int> v;
    if (numOfErrors == 0)
    {
        l = -1;
    }

    // for (int i = 0; i < numOfErrors; i++)
    // {
    //     cout << errorPosition[i] << " ";
    // }
    // cout << endl;

    // cout << col << "    row col     " << row << endl;

    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            if (m == l)
            {

                // cout << "error position:" << l << endl;
                int pos = col * i;
                pos += j;
                // cout << "pos:" << pos << endl;
                if (m < row * col)
                {
                    v.push_back(pos);
                    k++;
                    l = errorPosition[k];
                    receivedMatrix[i][j] = streamToSend[m++];
                }
            }
            else
            {
                receivedMatrix[i][j] = streamToSend[m++];
            }
        }
    }

    // cout<<"v size:"<<v.size()<<endl;
    int *errorPos = new int[v.size()];
    for (int i = 0; i < v.size(); i++)
    {
        errorPos[i] = v[i];
        // cout<<errorPos[i]<<" "<<v[i]<<endl;
    }

    // cout << k << endl;
    numOfErrors = v.size();
    sort(errorPos, errorPos + numOfErrors);
    // for (int i = 0; i < numOfErrors; i++)
    // {
    //     cout << errorPos[i] << " ";
    // }
    // cout << endl;

    cout << "data bits after column-wise deserialization and removing checksum:" << endl;
    k = 0;
    m = 0;
    l = errorPos[k];
    if (numOfErrors == 0)
    {
        l = -1;
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++, m++)
        {
            if (m == l)
            {
                cout << "\033[31m" << receivedMatrix[i][j] << "\033[0m";
                k++;
                l = errorPos[k];
            }
            else
            {
                cout << receivedMatrix[i][j];
            }
        }
        // cout<<endl<<l;
        cout << endl;
    }
    return errorPos;
}

void errorCorrection(bool **receivedMatrix, int row, int col)
{

    for (int i = 0; i < row; i++)
    {
        int l = 0;
        int k = 0;
        for (int j = 0; j < col; j++)
        {
            if (j == pow(2, l) - 1)
            {
                int hop = pow(2, l);
                bool checkbit = 0;
                for (int k = j; k < col; k += (hop + hop))
                {
                    for (int l = k; l < k + hop; l++)
                    {
                        if (l < col)
                        {
                            checkbit = checkbit ^ receivedMatrix[i][l];
                        }
                    }
                }
                if (checkbit)
                {
                    k += pow(2, l);
                }
                l++;
            }
        }
        if (k != 0)
        {
            receivedMatrix[i][k - 1] = receivedMatrix[i][k - 1] ^ 1;
        }
    }
    // cout << "data bits after error correction:" << endl;
    // for (int i = 0; i < row; i++)
    // {
    //     int l = 0;
    //     for (int j = 0; j < col; j++)
    //     {
    //         if (j == pow(2, l) - 1)
    //         {
    //             cout << "\033[32m" << receivedMatrix[i][j] << "\033[0m";
    //             l++;
    //         }
    //         else
    //         {
    //             cout << receivedMatrix[i][j];
    //         }
    //     }
    //     cout << endl;
    // }
}
void recoverMessage(bool **receivedMatrix, int row, int col, string &s)
{

    for (int i = 0; i < row; i++)
    {
        char c = 0;
        int count = 0;
        for (int j = 0; j < col; j++)
        {

            c = c | (receivedMatrix[i][j] << (7 - count));
            count++;
            if (count == 8)
            {
                s += c;
                c = 0;
                count = 0;
            }
        }
    }
    // for (int i = 0; i < row; i++)
    // {
    //     char c = 0;
    //     int count = 0;
    //     int k = 0;
    //     for (int j = 0; j < col; j++)
    //     {
    //         if (j == pow(2, k) - 1)
    //         {
    //             k++;
    //         }
    //         else
    //         {
    //             // c = c | (receivedMatrix[i][j] << (7 - count));
    //             // count++;
    //             // if (count == 8)
    //             // {
    //             //     s += c;
    //             //     c = 0;
    //             //     count = 0;
    //             // }
    //             c = c | (receivedMatrix[i][j] << (7 - count));
    //             count++;
    //             if (count == 8)
    //             {
    //                 s += c;
    //                 c = 0;
    //                 count = 0;
    //             }
    //         }
    //     }
    // }
    cout << "Recovered message:" << s << endl;
}

void remooveCheckbits(bool **receivedMatrix2, bool **receivedMatrix, int row, int col, int m)
{
    for (int i = 0; i < row; i++)
    {
        int k = 0;
        for (int j = 0; j < col; j++)
        {
            if (j == pow(2, k) - 1)
            {
                k++;
            }
            else
            {
                receivedMatrix2[i][j - k] = receivedMatrix[i][j];
            }
        }
    }
    cout << "data block after removing checkbits:" << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << receivedMatrix2[i][j];
        }
        cout << endl;
    }
}
int main()
{
    string s;
    int m, CRC;
    double p;
    bool **matrix;

    // freopen("input.txt", "r", stdin);

    cout << "Enter data string:";
    getline(cin, s);
    cout << "Enter number of data bytes in a row<m>:";
    cin >> m;
    cout << "Enter probability<p>:";
    cin >> p;
    cout << "Enter generator polynomial:";
    cin >> CRC;
    cout << endl
         << endl;

    // print input
    // cout << "Data string:" << s << endl;
    // cout << "Number of data bytes in a row<m>:" << m << endl;
    // cout << "Probability<p>:" << p << endl;
    // cout << "Generator polynomial:" << CRC << endl;
    // cout << endl
    //      << endl;
    // cout << endl
    //      << endl;
    // end of input print

    AddPadding(s, m);
    cout << "data string after padding:" << s << endl
         << endl;
    int numOfRows = s.length() / m;
    matrix = new bool *[numOfRows];
    for (int i = 0; i < numOfRows; i++)
    {
        matrix[i] = new bool[m * 8];
    }
    for (int i = 0; i < numOfRows; i++)
    {
        for (int j = 0; j < m * 8; j++)
        {
            matrix[i][j] = (s[i * m + j / 8] >> (7 - j % 8)) & 1;
        }
    }

    // print matrix
    cout << "data block <ascii code of m characters per row>:" << endl;
    printMatrix(matrix, numOfRows, m * 8);
    cout << endl;

    // required num of checkbits per row
    int checkbits = calculateCheckBits(m * 8);
    int col = m * 8 + checkbits;
    bool **checkbitMatrix = new bool *[numOfRows];
    for (int i = 0; i < numOfRows; i++)
    {
        checkbitMatrix[i] = new bool[col];
    }
    // add checkbits to checkbitMatrix
    for (int i = 0; i < numOfRows; i++)
    {
        int k = 0;
        for (int j = 0; j < col; j++)
        {
            if (j == pow(2, k) - 1)
            {
                checkbitMatrix[i][j] = 0;
                k++;
            }
            else
            {
                checkbitMatrix[i][j] = matrix[i][j - k];
            }
        }
    }
    for (int i = 0; i < numOfRows; i++)
    {
        int k = 0;
        for (int j = 0; j < col; j++)
        {
            if (j == pow(2, k) - 1)
            {
                int hop = pow(2, k);
                bool checkbit = 0;
                for (int k = j; k < col; k += (hop + hop))
                {
                    for (int l = k; l < k + hop; l++)
                    {
                        if (l < col)
                        {
                            checkbit = checkbit ^ checkbitMatrix[i][l];
                        }
                    }
                }
                checkbitMatrix[i][j] = checkbit;
                k++;
            }
        }
    }

    cout << "data block after adding checkbits" << endl;
    printCheckbitMatrix(checkbitMatrix, numOfRows, col);
    cout << endl;

    // columnwiseSerialize
    bool *streamToSend = new bool[col * (numOfRows)];
    columnwiseSerialize(checkbitMatrix, streamToSend, numOfRows, col);
    cout << endl;

    int crcLen = 0;
    int *crcArray = calculateCRC(CRC, &crcLen);

    // cout<<"crc array:"<<endl;
    // for(int i=0;i<crcLen+1;i++)
    // {
    //     cout<<crcArray[i];
    // }
    // cout<<endl;
    // cout<<"crc length:"<<crcLen<<endl;

    // add crc Checksum
    streamToSend = addCRCChecksum(streamToSend, col * numOfRows, crcArray, crcLen);
    cout << endl;

    int totalLen = col * (numOfRows) + crcLen;

    // for (int i = 0; i < totalLen; i++)
    // {
    //     cout << streamToSend[i];
    // }

    // add error
    int *errorPosition;
    int numOfErrors;
    errorPosition = addError(streamToSend, totalLen, p, &numOfErrors);
    // cout << endl << "Num Of Errors:" << numOfErrors << endl;

    // cout<<"crc length:"<<crcLen<<endl;
    // cout<<"num of errors:"<<numOfErrors<<endl;
    // cout<<"error position:"<<endl;
    // for(int i=0;i<numOfErrors;i++)
    // {
    //     cout<<errorPosition[i]<<" ";
    // }
    // cout<<endl;

    // error detection
    errorDetection(streamToSend, totalLen, crcArray, crcLen);

    bool* receivedFrame=removeChecksumBits(streamToSend, totalLen, crcLen);

    // columnwiseDeserialize
    bool **receivedMatrix = new bool *[numOfRows];
    for (int i = 0; i < numOfRows; i++)
    {
        receivedMatrix[i] = new bool[col];
    }
    int *errorPosition2;
    errorPosition2 = deserialiseColumnwise(receivedMatrix, streamToSend, errorPosition, numOfRows, col, totalLen - crcLen, numOfErrors);
    cout << endl;
    // for(int i=0;i<numOfRows;i++)
    // {
    //     for(int j=0;j<col;j++)
    //     {
    //         cout<<receivedMatrix[i][j];
    //     }
    //     cout<<endl;
    // }

    // error correction

    errorCorrection(receivedMatrix, numOfRows, col);
    string s2 = "";

    // remove checkbits
    bool **receivedMatrix2 = new bool *[numOfRows];
    for (int i = 0; i < numOfRows; i++)
    {
        receivedMatrix2[i] = new bool[m * 8];
    }
    remooveCheckbits(receivedMatrix2, receivedMatrix, numOfRows, col, m * 8);
    recoverMessage(receivedMatrix2, numOfRows, m * 8, s2);
}