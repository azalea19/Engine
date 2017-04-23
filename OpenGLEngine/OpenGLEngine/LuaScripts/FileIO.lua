
function string:split(delimiter, nMax)
   assert(delimiter ~= '')	--The delimiter used to split the string (comma in CSV)

    if nMax and nMax < 1 then	--check if nMax is negative
		nMax = nil
	end
   
   local splitString = {}	--table for the split up string

   if self:len() > 0 then 	--Only split string if it is onger than 0 chars	
		nMax = nMax or -1
   
      local fieldIndex = 1
	  local firstSearch = 1
      local nFirst,nLast = self:find(delimiter, firstSearch)		--find the first and last points to a delimiter
      while nFirst and nMax ~= 0 do				--As long as the first posistion of the string is not 0
         splitString[fieldIndex] = self:sub(firstSearch, nFirst-1) --gets a substring fom the start and end of the delimiter search
         fieldIndex = fieldIndex+1	--Increases the index by 1
         firstSearch = nLast+1	--Sets the first index to start searching for the delimiter at the location of th last comma + 1
         nFirst,nLast = self:find(delimiter, firstSearch) --find the start and end location of the new sub string
		 nMax = nMax - 1	--decrease nMax by 1
      end
      splitString[fieldIndex] = self:sub(firstSearch)	--Get the last part of the line (which has no delimiter)
   end

   return splitString	--the split up string table
end

function read(path, delimiter)		--Read in a CSV, and split up the string into a series of substrings based on a delimiter
    delimiter = delimiter or ','	--The delimiter to use (defaults to a comma (CSV)
    local csvFile = {}				--the csv data stored in a table as substrings
    local file = assert(io.open(path, "r"))		--Open the specified file for reading
    for line in file:lines() do					--for every line in the file
        dataTable = line:split(delimiter)		--Split up the current line into substrings
            for i=1,#dataTable do				--For each substring in the current line
                local data = dataTable[i]		--put this substring into a temporary storage area
                if data == '' then				--deterimine if the substring is null
                    dataTable = ''				--if it is, then this line is blank
                end	
                dataTable[i] = tonumber(data) or data	--convert the data from above into a number (if it can be converted)
            end
        table.insert(csvFile, dataTable)	--Insert the lines table of substrings/numbers into the csvFile storage
    end
    file:close()		--close the file
    return csvFile		--return the csvFile data
end

function write(path, data)					--Append a piece of data to a file
  local file = assert(io.open(path, "a"))	--open the file for appending
  file:write(data)							--Write the data to the file
  file:close()								--Close the file
end

function clearFile(path)
	local file = assert(io.open(path, "w+"))
	file:close()
end
