from copy import deepcopy

MAP_FILE = 'cave_map.txt'
HELP_FILE = 'help.txt'
ori_map = ('S', 'F', '*', '-', '@')
piece = ('🏠', '🏺', '🟢', '🧱', '🧝')

def load_map(map_file: str) -> list[list[str]]:
    """
    Loads a map from a file as a grid (list of lists)
    """
    # TODO: implement this function
    
    with open(map_file, 'r', encoding = 'utf-8') as file:
        
        grid = []
        map = file.readlines()
        
        for lines in map:
            
            lines = lines.strip()
            rows = []
            
            for char in range(len(lines)):
                
                rows.append(lines[char])
            
            grid.append(rows)    
            
    return grid

def find_start(grid: list[list[str]]) -> list[int, int]:
    """
    Finds the starting position of the player on the map.
    """
    # TODO: implement this function
    
    s_position = None
    
    for rows in range(len(grid)):
        
        for cols in range(len(grid[0])):
            
            if grid[rows][cols] == 'S':
                
                s_position = [rows, cols]
                
    return s_position

def get_command() -> str:
    """
    Gets a command from the user.
    """
    # TODO: implement this function
    
    command = input('Please enter your command:')
    
    return command

def display_map(grid: list[list[str]], player_position: list[int, int]) -> None:
    """
    Displays the map.
    """
    # TODO: implement this function
    
    row = player_position[0]
    col = player_position[1]
    new_grid = deepcopy(grid)
    
    new_grid[row][col] = '@'  
    
    for rows in new_grid:
        
        for chars in rows:
            
            idx = ori_map.index(chars)
            chars = piece[idx]
            
            print(chars, end = '')
        
        print()
        


def get_grid_size(grid: list[list[str]]) -> list[int, int]:
    """
    Returns the size of the grid.
    """
    # TODO: implement this function
    
    rows = len(grid)
    cols = len(grid[0])
    
    return [rows,cols]
    
def is_inside_grid(grid: list[list[str]], position: list[int, int]) -> bool:
    """
    Checks if a given position is valid (inside the grid).
    """
    grid_rows, grid_cols = get_grid_size(grid)
    # TODO: implement the rest of the function
    
    if 0 <= position[0] <= (grid_rows-1) and 0 <= position[1] <= (grid_cols-1):
        return True
    
    else:
        return False

def look_around(grid: list[list[str]], player_position: list[int, int]) -> list:
    """
    Returns the allowed directions.
    """
    allowed_objects = ('S', 'F', '*')
    row = player_position[0]
    col = player_position[1]
    directions = []
    if is_inside_grid(grid, [row - 1, col]) and grid[row - 1][col] in allowed_objects:
        directions.append('north')
    # TODO: implement the rest of the function
    
    if is_inside_grid(grid, [row + 1, col]) and grid[row + 1][col] in allowed_objects:
        
        directions.append('south')
    
    if is_inside_grid(grid, [row, col - 1]) and grid[row][col - 1] in allowed_objects:
        
        directions.append('west')
    
    if is_inside_grid(grid, [row, col + 1]) and grid[row][col + 1] in allowed_objects:
        
        directions.append('east')
        
    return directions

def move(direction: str, player_position: list[int, int], grid: list[list[str]]) -> bool:
    """
    Moves the player in the given direction.
    """
    # TODO: implement this function
    
    directions = look_around(grid, player_position)
    
    if direction in directions:
        
        if direction == 'north':
            player_position[0] = player_position[0] - 1
            
        elif direction == 'south':
            player_position[0] = player_position[0] + 1
            
        elif direction == 'west':
            player_position[1] = player_position[1] - 1
        
        elif direction == 'east':
            player_position[1] = player_position[1] + 1
            
        return True
    
    else:
        return False
    
def check_finish(grid: list[list[str]], player_position: list[int, int]) -> bool:
    """
    Checks if the player has reached the exit.
    """
    # TODO: implement this function
    
    for rows in range(len(grid)):
        
        for cols in range(len(grid[0])):
            
            if grid[rows][cols] == 'F':
                
                f_position = [rows, cols]
                
    if player_position == f_position:
        
        return True

    return False

def display_help() -> None:
    """
    Displays a list of commands.
    """
    # TODO: implement this function
    
    with open(HELP_FILE, 'r', encoding = 'utf-8') as file:
        
        help = file.read()
        
    print(help)


def main():
    """
    Main entry point for the game.
    """
    # TODO: update the main() function
    
    grid = load_map(MAP_FILE)
    s_position = find_start(grid)
    player_position = find_start(grid)
    display_map(grid, player_position)
    
    print(f"Player's position:{s_position}")
    
    command = get_command()
        
    while True:
        
        if command == 'show map':
            display_map(grid, player_position)
        
        elif command == 'escape':
            break
        
        elif command in ['go north', 'go south', 'go west', 'go east']:
            
            if move(command[3:], player_position, grid):
                    print(f"You moved {command[3:]}.")
                
            else:
                print('There is no way there.')
        
        elif command == 'help':
                
            display_help()
            
        else:
            print('I do not understand.')
        
        if check_finish(grid, player_position):
            print('Congratulations! You have reached the exit!')
            break
        
        else:
            directions = look_around(grid, player_position)
            print(directions)            
            command = get_command()
    

if __name__ == '__main__':
    main()
