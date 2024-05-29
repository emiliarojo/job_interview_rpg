#include "load_config.h"
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadGameConfiguration(Character *player, Scenario scenarios[], Skill availableSkills[], int *numSkills) {
    FILE *fp = fopen("game_config.json", "r");
    if (fp == NULL) {
        perror("Error opening game_config.json");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0L, SEEK_END);
    long buffer_size = ftell(fp);
    rewind(fp);

    char *buffer = (char *)malloc(buffer_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory for JSON buffer");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(buffer, sizeof(char), buffer_size, fp);
    if (bytesRead != buffer_size) {
        perror("Error reading game_config.json");
        fclose(fp);
        free(buffer);
        exit(EXIT_FAILURE);
    }
    buffer[bytesRead] = '\0';
    fclose(fp);

    struct json_object *parsed_json;
    struct json_object *character;
    struct json_object *skills;
    struct json_object *skill;
    struct json_object *scenarios_json;
    struct json_object *scenario;
    struct json_object *questions;
    struct json_object *question;

    parsed_json = json_tokener_parse(buffer);
    if (!parsed_json) {
        fprintf(stderr, "Error parsing JSON data: %s\n", json_tokener_error_desc(json_tokener_get_error(NULL)));
        free(buffer);
        exit(EXIT_FAILURE);
    }

    if (!json_object_object_get_ex(parsed_json, "character", &character)) {
        fprintf(stderr, "Error: No character information in JSON data\n");
        json_object_put(parsed_json);  // Free parsed JSON object
        free(buffer);
        exit(EXIT_FAILURE);
    }
    if (!json_object_object_get_ex(parsed_json, "skills", &skills)) {
        fprintf(stderr, "Error: No skills information in JSON data\n");
        json_object_put(parsed_json);
        free(buffer);
        exit(EXIT_FAILURE);
    }
    if (!json_object_object_get_ex(parsed_json, "scenarios", &scenarios_json)) {
        fprintf(stderr, "Error: No scenarios information in JSON data\n");
        json_object_put(parsed_json);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    strcpy(player->name, json_object_get_string(json_object_object_get(character, "name")));
    player->hp = json_object_get_int(json_object_object_get(character, "hp"));
    player->atk = json_object_get_int(json_object_object_get(character, "atk"));
    player->def = json_object_get_int(json_object_object_get(character, "def"));

    printf("Loaded character: %s, HP: %d, ATK: %d, DEF: %d\n", player->name, player->hp, player->atk, player->def);

    int skills_len = json_object_array_length(skills);
    for (int i = 0; i < skills_len; i++) {
        skill = json_object_array_get_idx(skills, i);
        strcpy(availableSkills[i].name, json_object_get_string(json_object_object_get(skill, "name")));
        strcpy(availableSkills[i].description, json_object_get_string(json_object_object_get(skill, "description")));
        availableSkills[i].type = json_object_get_int(json_object_object_get(skill, "type"));
        availableSkills[i].atkModifier = json_object_get_int(json_object_object_get(skill, "atkModifier"));
        availableSkills[i].defModifier = json_object_get_int(json_object_object_get(skill, "defModifier"));
        printf("Loaded skill %d: %s\n", i + 1, availableSkills[i].name);
    }
    *numSkills = skills_len;

    int scenarios_len = json_object_array_length(scenarios_json);
    for (int i = 0; i < scenarios_len; i++) {
        scenario = json_object_array_get_idx(scenarios_json, i);
        strcpy(scenarios[i].name, json_object_get_string(json_object_object_get(scenario, "name")));
        strcpy(scenarios[i].description, json_object_get_string(json_object_object_get(scenario, "description")));
        json_object *interviewer;
        if (!json_object_object_get_ex(scenario, "interviewer", &interviewer)) {
            fprintf(stderr, "Error: No interviewer information for scenario %d\n", i);
            json_object_put(parsed_json);
            free(buffer);
            exit(EXIT_FAILURE);
        }
        strcpy(scenarios[i].interviewer.name, json_object_get_string(json_object_object_get(interviewer, "name")));
        scenarios[i].interviewer.hp = json_object_get_int(json_object_object_get(interviewer, "hp"));
        scenarios[i].interviewer.atk = json_object_get_int(json_object_object_get(interviewer, "atk"));
        scenarios[i].interviewer.def = json_object_get_int(json_object_object_get(interviewer, "def"));

        printf("Loaded scenario %d: %s\n", i + 1, scenarios[i].name);

        if (!json_object_object_get_ex(scenario, "questions", &questions)) {
            fprintf(stderr, "Error: No questions information for scenario %d\n", i);
            json_object_put(parsed_json);
            free(buffer);
            exit(EXIT_FAILURE);
        }
        int questions_len = json_object_array_length(questions);
        scenarios[i].questionCount = questions_len;
        for (int j = 0; j < questions_len; j++) {
            question = json_object_array_get_idx(questions, j);
            strcpy(scenarios[i].questions[j].text, json_object_get_string(json_object_object_get(question, "text")));
            for (int k = 0; k < MAX_OPTIONS; k++) {
                char option_key[10];
                sprintf(option_key, "option%d", k + 1);
                strcpy(scenarios[i].questions[j].options[k], json_object_get_string(json_object_object_get(question, option_key)));

                char hp_key[10];
                sprintf(hp_key, "hp%d", k + 1);
                scenarios[i].questions[j].hpImpacts[k] = json_object_get_int(json_object_object_get(question, hp_key));

                char atk_key[10];
                sprintf(atk_key, "atk%d", k + 1);
                scenarios[i].questions[j].atkImpacts[k] = json_object_get_int(json_object_object_get(question, atk_key));

                char def_key[10];
                sprintf(def_key, "def%d", k + 1);
                scenarios[i].questions[j].defImpacts[k] = json_object_get_int(json_object_object_get(question, def_key));
            }
            printf("Loaded question %d for scenario %d\n", j + 1, i + 1);
        }
    }
    printf("Completed loading game configuration.\n");

    // Clean up JSON objects
    json_object_put(parsed_json);
    free(buffer);
}
