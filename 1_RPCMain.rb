module Discord

    MOD_DIR = File.dirname(__FILE__)
    DLL_PATH = "#{MOD_DIR}/lonarpg_rpc.dll"

    Win32API.new(DLL_PATH, 'loadLibraries', 'P', 'V').call(MOD_DIR)

    DISCORD_UPDATE_W32   = Win32API.new(DLL_PATH, 'discordUpdate', ['P', 'I', 'I', 'I', 'P'], 'V')
    DISCORD_INIT_W32     = Win32API.new(DLL_PATH, 'discordInit', 'V', 'V')
    
    def self.update
        # 0 = HUMAN
        # 1 = DEEPONE
        # 2 = SEA WITCH
        # 3 = MIXED
        # 4 = ABOMINATION
        @race = 0
        @lvl = 0
        if $game_player.actor
            @lvl = $game_player.actor.level
            @racestr = $game_player.actor.record_lona_race

            case @racestr
            when "PreDeepone"
                @race = 1
            when "TrueDeepone"
                @race = 2
            when "Moot"
                @race = 3
            when "Abomination"
                @race = 4
            end
        end

        @date = ""
        if $game_date.date
            @date = "#{$game_date.date[0]}.#{$game_date.date[1]}.#{$game_date.date[2]}"
        end

        local_ver = $data_system.game_title.split('.')
        @ver = "#{local_ver[1]}.#{local_ver[2]}.#{local_ver[3]}.#{local_ver[4]}"
        
        print("UPDATE #{@gameState}")
        DISCORD_UPDATE_W32.call(@ver, @lvl, @gameState, @race, @date)
    end

    def self.gameState=(state)
        @gameState = state
    end

    DISCORD_INIT_W32.call
end

class TitleMenu < Sprite
	alias originit initialize
	def initialize
		originit
        Discord.gameState = 0
        Discord.update
	end
end

class Scene_Map < Scene_Base
    alias discord_rpc_startdd start
	def start
		discord_rpc_startdd
        Discord.gameState = $game_system.menu_disabled ? 0 : 1
        Discord.update
	end
end

class Game_Actor < Game_Battler
    alias origsetstate set_action_state
    
    def set_action_state(action_state, force=false)
		origsetstate(action_state, force)
        if action_state.to_s == "sex"
            Discord.gameState = 2
        else
            Discord.gameState = 1
        end
        Discord.update
	end
end