import { FontAwesome } from "@expo/vector-icons";
import React from "react";
import {View, Text, Pressable, StyleSheet, Animated} from 'react-native'

export default function TestEvent() {
    return(        
        <Pressable style={styles.eventContainer}>
            <Text style={styles.cuffName}>RUA</Text>
            <View style={styles.volumeContainer}>
                <FontAwesome name='volume-up' size={40} color="grey"/>
            </View>
            <View style={styles.example}>
            </View>
        </Pressable>
    )
}

const styles = StyleSheet.create({
    test: {
        backgroundColor:'red'
    },
    eventContainer: {
        flexDirection: 'row',
        margin: 10,
        height: 80,
        width: 320,
        borderRadius: 15,
        backgroundColor: 'white',
        justifyContent: 'flex-start',
        alignItems: 'center',
    },
    cuffName: {
        fontSize: 40,
        marginLeft: 30,
        color: 'grey',
    },
    volumeContainer: {
        marginLeft: 140,
        color: 'grey'
    },
    absoluteFill: {

    },example: {
        marginVertical: 24,
        
    },
})

//waist
//RUA
//RW
//N
//LW
//LUA